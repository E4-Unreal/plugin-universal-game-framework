// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActor.h"

#include "Components/InventoryComponent.h"
#include "Data/ItemInstance.h"
#include "GameplayTags/InventoryGameplayTags.h"
#include "Interfaces/ItemDataInterface.h"

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Config */

    InteractionType = Interaction::Item;

    // 아이템 외 5개
    InteractionMessage = NSLOCTEXT("InventorySystem", "PickupMessage", "{0} +{1}");

    /* DisplayMesh */

    GetDisplayMesh()->SetSimulatePhysics(true);
}

FText AItemActor::GetInteractionMessage_Implementation() const
{
    if (!ItemInstances.IsEmpty())
    {
        auto Data = ItemInstances[0]->GetData();
        if (Data && Data->Implements<UItemDataInterface>())
        {
            FText ItemDisplayName = IItemDataInterface::Execute_GetDisplayNameText(Data);

            return ItemInstances.Num() == 1 ? ItemDisplayName : FText::Format(InteractionMessage, ItemDisplayName, FText::FromString(FString::FromInt(ItemInstances.Num() - 1)));
        }
    }

    return FText::GetEmpty();
}

void AItemActor::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    if (auto InventoryComponent = Interactor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& InventoryItem : ItemInstances)
        {
            if (InventoryItem) InventoryComponent->AddContent(InventoryItem);
        }

        if (bAutoDestroy) Destroy();
    }
}

void AItemActor::SetItemInstances_Implementation(const TArray<UDataInstanceBase*>& NewItemsInstances)
{
    ItemInstances = NewItemsInstances;

    Refresh();
}

void AItemActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActor::BeginPlay()
{
    if (ItemInstances.IsEmpty())
    {
        Destroy();
    }
    else
    {
        Super::BeginPlay();
    }
}

#if WITH_EDITOR
void AItemActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultStaticMesh) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, ItemInstances)
        )
    {
        Refresh();
    }
}
#endif

void AItemActor::Refresh()
{
    GetDisplayMesh()->SetStaticMesh(GetStaticMesh());
}

UStaticMesh* AItemActor::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (ItemInstances.Num() == 1)
    {
        if (auto ItemInstance = ItemInstances.Last())
        {
            if (UDataAsset* Data = ItemInstance->GetData())
            {
                StaticMesh = IItemDataInterface::Execute_GetStaticMesh(Data).LoadSynchronous();
            }
        }
    }

    return StaticMesh ? StaticMesh : DefaultStaticMesh.LoadSynchronous();
}
