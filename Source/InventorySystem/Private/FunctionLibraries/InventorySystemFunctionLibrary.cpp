// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/InventorySystemFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/ItemActorInterface.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/ItemInstanceInterface.h"

AActor* UInventorySystemFunctionLibrary::SpawnItemActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass,
                                                        UDataInstanceBase* ItemInstance, const FVector& Offset)
{
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

TArray<AActor*> UInventorySystemFunctionLibrary::SpawnItemActors(AActor* Owner, TSubclassOf<AActor> ItemActorClass,
                                                         const TArray<UDataInstanceBase*>& ItemInstances, const FVector& Offset)
{
    TArray<AActor*> SpawnedItemActors;
    SpawnedItemActors.Reserve(ItemInstances.Num());

    for (const auto& ItemInstance : ItemInstances)
    {
        if (AActor* SpawnedItemActor = SpawnItemActor(Owner, ItemActorClass, ItemInstance, Offset))
        {
            SpawnedItemActors.Emplace(SpawnedItemActor);
        }
    }

    return SpawnedItemActors;
}

AActor* UInventorySystemFunctionLibrary::SpawnItemPackageActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass,
    const TArray<UDataInstanceBase*>& ItemInstances, const FVector& Offset)
{
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

UDataAsset* UInventorySystemFunctionLibrary::GetItemData(UDataDefinitionBase* Definition)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UItemDataInterface>(Definition);
}

int32 UInventorySystemFunctionLibrary::GetMaxStack(UDataDefinitionBase* Definition)
{
    auto ItemData = GetItemData(Definition);

    return ItemData ? IItemDataInterface::Execute_GetMaxStack(ItemData) : 0;
}

FGameplayTag UInventorySystemFunctionLibrary::GetItemType(UDataDefinitionBase* Definition)
{
    auto ItemData = GetItemData(Definition);

    return ItemData ? IItemDataInterface::Execute_GetItemType(ItemData) : FGameplayTag::EmptyTag;
}

UDataInstanceBase* UInventorySystemFunctionLibrary::CreateItemInstance(UDataDefinitionBase* Definition)
{
    if (Definition)
    {
        auto DataInstance = UDataManagerFunctionLibrary::CreateDataInstance(Definition);
        auto ItemInstance = GetItemInstance(DataInstance);

        return ItemInstance ? DataInstance : nullptr;
    }

    return nullptr;
}

UObject* UInventorySystemFunctionLibrary::GetItemInstance(UDataInstanceBase* DataInstance)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UItemInstanceInterface>(DataInstance);
}

int32 UInventorySystemFunctionLibrary::GetQuantity(UDataInstanceBase* DataInstance)
{
    auto ItemInstance = GetItemInstance(DataInstance);

    return ItemInstance ? IItemInstanceInterface::Execute_GetQuantity(ItemInstance) : 0;
}

void UInventorySystemFunctionLibrary::SetQuantity(UDataInstanceBase* DataInstance, int32 NewQuantity)
{
    if (auto ItemInstance = GetItemInstance(DataInstance))
    {
        IItemInstanceInterface::Execute_SetQuantity(ItemInstance, NewQuantity);
    }
}
