// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemActorComponent.h"

#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemDataInterface.h"


UItemActorComponent::UItemActorComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ItemNameFormat = NSLOCTEXT("InventorySystem", "PickupMessage", "{0} +{1}"); // 아이템 외 5개
}

#if WITH_EDITOR
void UItemActorComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
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

void UItemActorComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindDisplayMesh();
    Refresh();
}

void UItemActorComponent::SetDisplayMesh(UStaticMeshComponent* NewDisplayMesh)
{
    DisplayMesh = NewDisplayMesh;
}

void UItemActorComponent::FindDisplayMesh()
{
    if (DisplayMesh.IsValid()) return;

    DisplayMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}

FText UItemActorComponent::GetItemName() const
{
    if (!ItemInstances.IsEmpty())
    {
        auto Data = ItemInstances[0]->GetData();
        if (Data && Data->Implements<UItemDataInterface>())
        {
            FText ItemDisplayName = IItemDataInterface::Execute_GetDisplayNameText(Data);

            return ItemInstances.Num() == 1 ? ItemDisplayName : FText::Format(ItemNameFormat, ItemDisplayName, FText::FromString(FString::FromInt(ItemInstances.Num() - 1)));
        }
    }

    return FText::GetEmpty();
}

void UItemActorComponent::SetItems(const TArray<UDataInstanceBase*>& NewItemInstances)
{
    Super::SetItems(NewItemInstances);

    Refresh();
}

void UItemActorComponent::Refresh()
{
    if (DisplayMesh.IsValid())
    {
        DisplayMesh->SetStaticMesh(GetStaticMesh());
    }
}

UStaticMesh* UItemActorComponent::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (ItemInstances.Num() == 1)
    {
        if (auto ItemInstance = ItemInstances.Last())
        {
            if (UDataAsset* Data = ItemInstance->GetData())
            {
                if (Data->Implements<UItemDataInterface>())
                {
                    StaticMesh = IItemDataInterface::Execute_GetStaticMesh(Data).LoadSynchronous();
                }
            }
        }
    }

    return StaticMesh ? StaticMesh : DefaultStaticMesh.LoadSynchronous();
}
