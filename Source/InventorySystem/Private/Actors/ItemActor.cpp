// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActor.h"

#include "Components/InventoryComponent.h"
#include "Data/ItemInstance.h"
#include "Interfaces/ItemDataInterface.h"

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    auto DisplayStaticMesh = GetDisplayStaticMesh();
    DisplayStaticMesh->SetSimulatePhysics(true);
}

void AItemActor::SetInventoryItems_Implementation(const TArray<UItemInstance*>& NewInventoryItems)
{
    InventoryItems = NewInventoryItems;

    Refresh();
}

void AItemActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActor::BeginPlay()
{
    if (InventoryItems.IsEmpty())
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
        PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, InventoryItems)
        )
    {
        Refresh();
    }
}
#endif

void AItemActor::OnInteractionTriggered_Implementation(AActor* Interactor)
{
    Super::OnInteractionTriggered_Implementation(Interactor);

    if (auto InventoryComponent = Interactor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& InventoryItem : InventoryItems)
        {
            if (InventoryItem) InventoryComponent->AddContent(InventoryItem);
        }

        if (bAutoDestroy) Destroy();
    }
}

void AItemActor::Refresh()
{
    GetDisplayStaticMesh()->SetStaticMesh(GetStaticMesh());
}

UStaticMesh* AItemActor::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (InventoryItems.Num() == 1)
    {
        UObject* Content = InventoryItems.Last();
        if (UDataAsset* Data = IDataInstanceInterface::Execute_GetData(Content))
        {
            StaticMesh = IItemDataInterface::Execute_GetStaticMesh(Data).LoadSynchronous();
        }
    }

    return StaticMesh ? StaticMesh : DefaultStaticMesh.LoadSynchronous();
}
