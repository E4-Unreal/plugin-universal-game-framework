// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystemFunctionLibrary.h"

#include "Actors/ItemActorBase.h"
#include "Types/ItemContainer.h"

UItemDefinition* UItemSystemFunctionLibrary::GetItemDefinition(const FItemContainer& ItemData)
{
    return ItemData.GetItemDefinition();
}

AItemActorBase* UItemSystemFunctionLibrary::SpawnItemActor(AActor* Owner, TSubclassOf<AItemActorBase> ItemActorClass, const FItemContainer& ItemContainer, const FTransform& SpawnTransform)
{
    if (Owner == nullptr || ItemActorClass == nullptr || ItemContainer.IsNotValid()) return nullptr;

    auto ItemActor = Owner->GetWorld()->SpawnActorDeferred<AItemActorBase>(ItemActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    ItemActor->ItemContainer = ItemContainer;
    ItemActor->FinishSpawning(SpawnTransform);

    return ItemActor;
}
