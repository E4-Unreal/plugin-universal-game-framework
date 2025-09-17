// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemDropComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Components/InventoryComponent.h"
#include "Data/DataInstanceBase.h"

UItemDropComponent::UItemDropComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    bAutoDestroy = true;

    SpawnOffset = FVector(0, 0, 50);
    ImpulseAngle = 90;
    ImpulseStrength = 1000;
}

void UItemDropComponent::BeginPlay()
{
    if (ItemInstances.IsEmpty())
    {
        GetOwner()->Destroy();
    }
    else
    {
        Super::BeginPlay();
    }
}

void UItemDropComponent::SetItems(const TArray<UObject*>& NewItemInstances)
{
    ItemInstances = NewItemInstances;
}

void UItemDropComponent::Clear()
{
    ItemInstances.Empty();

    if (bAutoDestroy) GetOwner()->Destroy();
}

void UItemDropComponent::TransferItemsToInventory(AActor* TargetActor)
{
    if (auto InventoryComponent = TargetActor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& InventoryItem : ItemInstances)
        {
            if (InventoryItem) InventoryComponent->AddContent(InventoryItem);
        }

        Clear();
    }
}

void UItemDropComponent::SpawnItems()
{
    if (ItemActorClass && !ItemInstances.IsEmpty())
    {
        const auto& SpawnedItemActors = UInventorySystemFunctionLibrary::SpawnItemActors(GetOwner(), ItemActorClass, ItemInstances, SpawnOffset);
        for (const auto& SpawnedItemActor : SpawnedItemActors)
        {
            UInventorySystemFunctionLibrary::ImpulseActor(SpawnedItemActor, ImpulseAngle, ImpulseStrength);
        }

        Clear();
    }
}
