// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemFunctionLibrary.h"

#include "Interfaces/ItemActorInterface.h"

AActor* UInventorySystemFunctionLibrary::SpawnItemActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass,
                                                     const TArray<UItemInstance*>& InventoryItems, const FVector& Offset)
{
    if (bool bCanSpawn = Owner && ItemActorClass && ItemActorClass->ImplementsInterface(UItemActorInterface::StaticClass()) && !InventoryItems.IsEmpty(); !bCanSpawn) return nullptr;

    UWorld* World = Owner->GetWorld();
    if (!World) return nullptr;

    FTransform SpawnTransform = Owner->GetActorTransform();
    SpawnTransform.SetLocation(SpawnTransform.GetLocation() + Owner->GetActorRotation().RotateVector(Offset));
    AActor* SpawnedItemActor = World->SpawnActorDeferred<AActor>(ItemActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    IItemActorInterface::Execute_SetInventoryItems(SpawnedItemActor, InventoryItems);
    SpawnedItemActor->FinishSpawning(SpawnTransform);

    return SpawnedItemActor;
}
