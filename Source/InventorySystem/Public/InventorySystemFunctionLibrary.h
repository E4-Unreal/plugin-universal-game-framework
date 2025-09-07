// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventorySystemFunctionLibrary.generated.h"

class UItemInstance;
class IItemActorInterface;

UCLASS()
class INVENTORYSYSTEM_API UInventorySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static AActor* SpawnItemActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass, const TArray<UItemInstance*>& InventoryItems, const FVector& Offset = FVector::ZeroVector);
};
