// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/InventorySystemFunctionLibrary.h"

#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/ItemActorInterface.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/ItemInstanceInterface.h"

AActor* UInventorySystemFunctionLibrary::SpawnItemActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass,
                                                        UObject* ItemInstance, const FVector& Offset)
{
    if (bool bCanSpawn = Owner && ItemActorClass && ItemActorClass->ImplementsInterface(UItemActorInterface::StaticClass()) && ItemInstance; !bCanSpawn) return nullptr;

    UWorld* World = Owner->GetWorld();
    if (!World) return nullptr;

    FTransform SpawnTransform = Owner->GetActorTransform();
    SpawnTransform.SetLocation(SpawnTransform.GetLocation() + Owner->GetActorRotation().RotateVector(Offset));
    AActor* SpawnedItemActor = World->SpawnActorDeferred<AActor>(ItemActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    TArray<UObject*> ItemInstances = { ItemInstance };
    IItemActorInterface::Execute_SetItemInstances(SpawnedItemActor, ItemInstances);
    SpawnedItemActor->FinishSpawning(SpawnTransform);

    return SpawnedItemActor;
}

TArray<AActor*> UInventorySystemFunctionLibrary::SpawnItemActors(AActor* Owner, TSubclassOf<AActor> ItemActorClass,
                                                         const TArray<UObject*>& ItemInstances, const FVector& Offset)
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
    const TArray<UObject*>& ItemInstances, const FVector& Offset)
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

UDataAsset* UInventorySystemFunctionLibrary::GetItemData(UObject* DataObject)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UItemDataInterface>(DataObject);
}

int32 UInventorySystemFunctionLibrary::GetMaxStack(UObject* DataObject)
{
    auto ItemData = GetItemData(DataObject);

    return ItemData ? IItemDataInterface::Execute_GetMaxStack(ItemData) : 0;
}

FGameplayTag UInventorySystemFunctionLibrary::GetItemType(UObject* DataObject)
{
    auto ItemData = GetItemData(DataObject);

    return ItemData ? IItemDataInterface::Execute_GetItemType(ItemData) : FGameplayTag::EmptyTag;
}

UObject* UInventorySystemFunctionLibrary::CreateItemInstance(UDataAsset* Data)
{
    auto InstanceData = UDataManagerFunctionLibrary::CreateInstanceData(Data);
    auto ItemData = GetItemData(InstanceData);
    auto ItemInstance = GetItemInstance(InstanceData);

    return ItemData && ItemInstance ? InstanceData : nullptr;
}

UObject* UInventorySystemFunctionLibrary::GetItemInstance(UObject* InstanceData)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UItemInstanceInterface>(InstanceData);
}

int32 UInventorySystemFunctionLibrary::GetQuantity(UObject* InstanceData)
{
    auto ItemInstance = GetItemInstance(InstanceData);

    return ItemInstance ? IItemInstanceInterface::Execute_GetQuantity(ItemInstance) : 0;
}

void UInventorySystemFunctionLibrary::SetQuantity(UObject* InstanceData, int32 NewQuantity)
{
    if (auto ItemInstance = GetItemInstance(InstanceData))
    {
        IItemInstanceInterface::Execute_SetQuantity(ItemInstance, NewQuantity);
    }
}
