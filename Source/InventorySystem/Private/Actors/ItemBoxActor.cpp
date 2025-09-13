// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemBoxActor.h"

#include "InventorySystemFunctionLibrary.h"


AItemBoxActor::AItemBoxActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SpawnOffset = FVector(0, 0, 100);
    ImpulseAngle = 90;
    ImpulseStrength = 2000;
}

void AItemBoxActor::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    for (const auto& ItemInstance : ItemInstances)
    {
        SpawnItem(ItemInstance);
    }
}

AActor* AItemBoxActor::SpawnItem(UDataInstanceBase* InItemInstance)
{
    if (AActor* SpawnedItemActor = UInventorySystemFunctionLibrary::SpawnItemActor(this, ItemActorClass, InItemInstance, SpawnOffset))
    {
        UInventorySystemFunctionLibrary::ImpulseActor(SpawnedItemActor, ImpulseAngle, ImpulseStrength);

        return SpawnedItemActor;
    }

    return nullptr;
}
