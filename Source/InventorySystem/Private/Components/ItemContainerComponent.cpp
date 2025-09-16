// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemContainerComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Components/InventoryComponent.h"
#include "Data/DataInstanceBase.h"

UItemContainerComponent::UItemContainerComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    bAutoDestroy = true;

    SpawnOffset = FVector(0, 0, 50);
    ImpulseAngle = 90;
    ImpulseStrength = 1000;
}

void UItemContainerComponent::BeginPlay()
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

void UItemContainerComponent::SetItems(const TArray<UObject*>& NewItemInstances)
{
    ItemInstances = NewItemInstances;
}

void UItemContainerComponent::Clear()
{
    ItemInstances.Empty();

    if (bAutoDestroy) GetOwner()->Destroy();
}

void UItemContainerComponent::TransferItemsToInventory(AActor* TargetActor)
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

void UItemContainerComponent::SpawnItems()
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
