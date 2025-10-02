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
    static AActor* SpawnItemActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass, UDataInstanceBase* ItemInstance, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static TArray<AActor*> SpawnItemActors(AActor* Owner, TSubclassOf<AActor> ItemActorClass, const TArray<UDataInstanceBase*>& ItemInstances, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static AActor* SpawnItemPackageActor(AActor* Owner, TSubclassOf<AActor> ItemActorClass, const TArray<UDataInstanceBase*>& ItemInstances, const FVector& Offset = FVector::ZeroVector);

    UFUNCTION(BlueprintCallable)
    static void ImpulseActor(AActor* Actor, float ImpulseAngle, float ImpulseStrength);
};
