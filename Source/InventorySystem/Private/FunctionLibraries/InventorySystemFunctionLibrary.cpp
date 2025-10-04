// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/InventorySystemFunctionLibrary.h"

#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemActorInterface.h"
#include "Settings/InventorySystemSettings.h"

AActor* UInventorySystemFunctionLibrary::SpawnItemActor(AActor* Owner, UDataInstanceBase* ItemInstance, TSubclassOf<AActor> ItemActorClass, const FVector& Offset)
{
    if (ItemActorClass == nullptr) ItemActorClass = UInventorySystemSettings::Get()->GetDefaultItemActorClass();

    if (bool bCanSpawn = Owner && ItemActorClass && ItemActorClass->ImplementsInterface(UItemActorInterface::StaticClass()) && ItemInstance; !bCanSpawn) return nullptr;

    UWorld* World = Owner->GetWorld();
    if (!World) return nullptr;

    FTransform SpawnTransform = Owner->GetActorTransform();
    SpawnTransform.SetLocation(SpawnTransform.GetLocation() + Owner->GetActorRotation().RotateVector(Offset));
    AActor* SpawnedItemActor = World->SpawnActorDeferred<AActor>(ItemActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    TArray ItemInstances = { ItemInstance };
    IItemActorInterface::Execute_SetItemInstances(SpawnedItemActor, ItemInstances);
    SpawnedItemActor->FinishSpawning(SpawnTransform);

    return SpawnedItemActor;
}

TArray<AActor*> UInventorySystemFunctionLibrary::SpawnItemActors(AActor* Owner, const TArray<UDataInstanceBase*>& ItemInstances, TSubclassOf<AActor> ItemActorClass, const FVector& Offset)
{
    TArray<AActor*> SpawnedItemActors;
    SpawnedItemActors.Reserve(ItemInstances.Num());

    for (const auto& ItemInstance : ItemInstances)
    {
        if (AActor* SpawnedItemActor = SpawnItemActor(Owner, ItemInstance, ItemActorClass, Offset))
        {
            SpawnedItemActors.Emplace(SpawnedItemActor);
        }
    }

    return SpawnedItemActors;
}

AActor* UInventorySystemFunctionLibrary::SpawnItemPackageActor(AActor* Owner, const TArray<UDataInstanceBase*>& ItemInstances, TSubclassOf<AActor> ItemActorClass, const FVector& Offset)
{
    if (ItemActorClass ==  nullptr) ItemActorClass = UInventorySystemSettings::Get()->GetDefaultItemActorClass();

    if (bool bCanSpawn = Owner && ItemActorClass && ItemActorClass->ImplementsInterface(UItemActorInterface::StaticClass()) && !ItemInstances.IsEmpty(); !bCanSpawn) return nullptr;

    UWorld* World = Owner->GetWorld();
    if (!World) return nullptr;

    FTransform SpawnTransform = Owner->GetActorTransform();
    SpawnTransform.SetLocation(SpawnTransform.GetLocation() + Owner->GetActorRotation().RotateVector(Offset));
    AActor* SpawnedItemActor = World->SpawnActorDeferred<AActor>(ItemActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    IItemActorInterface::Execute_SetItemInstances(SpawnedItemActor, ItemInstances);
    SpawnedItemActor->FinishSpawning(SpawnTransform);

    return SpawnedItemActor;
}

void UInventorySystemFunctionLibrary::ImpulseActor(AActor* Actor, float ImpulseAngle, float ImpulseStrength)
{
    if (Actor && !FMath::IsNearlyZero(ImpulseStrength))
    {
        if (auto Mesh = Actor->FindComponentByClass<UMeshComponent>())
        {
            float ImpulseRadian = FMath::DegreesToRadians(ImpulseAngle);
            FVector ImpulseDirection = FVector(FMath::Cos(ImpulseRadian), 0, FMath::Sin(ImpulseRadian));
            ImpulseDirection = ImpulseDirection.RotateAngleAxis(FMath::RandRange(0, 360), FVector::UpVector);
            Mesh->AddImpulse(ImpulseDirection * ImpulseStrength);
        }
    }
}
