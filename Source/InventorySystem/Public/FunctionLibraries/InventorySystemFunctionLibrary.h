// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventorySystemFunctionLibrary.generated.h"

class UDataInstanceBase;

UCLASS()
class INVENTORYSYSTEM_API UInventorySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static AActor* SpawnItemActor(AActor* Owner, UDataInstanceBase* ItemInstance, TSubclassOf<AActor> ItemActorClass = nullptr, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static TArray<AActor*> SpawnItemActors(AActor* Owner, const TArray<UDataInstanceBase*>& ItemInstances, TSubclassOf<AActor> ItemActorClass = nullptr, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static AActor* SpawnItemPackageActor(AActor* Owner, const TArray<UDataInstanceBase*>& ItemInstances, TSubclassOf<AActor> ItemActorClass = nullptr, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static void ImpulseActor(AActor* Actor, float ImpulseAngle, float ImpulseStrength);
};
