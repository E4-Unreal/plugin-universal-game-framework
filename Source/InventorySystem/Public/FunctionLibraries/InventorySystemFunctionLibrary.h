// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventorySystemFunctionLibrary.generated.h"

struct FGameplayTag;

UCLASS()
class INVENTORYSYSTEM_API UInventorySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static AActor* SpawnItemActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass, UObject* ItemInstance, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static TArray<AActor*> SpawnItemActors(AActor* Owner, TSubclassOf<AActor> ItemActorClass, const TArray<UObject*>& ItemInstances, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static AActor* SpawnItemPackageActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass, const TArray<UObject*>& ItemInstances, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static void ImpulseActor(AActor* Actor, float ImpulseAngle, float ImpulseStrength);

    /* ItemData */

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static UDataAsset* GetItemData(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static int32 GetMaxStack(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "ItemData")
    static FGameplayTag GetItemType(UObject* DataObject);

    /* ItemInstanceData */

    UFUNCTION(BlueprintPure, Category = "ItemInstanceData")
    static UObject* CreateItemInstance(UDataAsset* Data);

    UFUNCTION(BlueprintPure, Category = "ItemInstanceData")
    static UObject* GetItemInstance(UObject* InstanceData);

    UFUNCTION(BlueprintPure, Category = "ItemInstanceData")
    static int32 GetQuantity(UObject* InstanceData);

    UFUNCTION(BlueprintCallable, Category = "ItemInstanceData")
    static void SetQuantity(UObject* InstanceData, int32 NewQuantity);
};
