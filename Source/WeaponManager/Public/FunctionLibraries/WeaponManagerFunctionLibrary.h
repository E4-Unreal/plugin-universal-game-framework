// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponManagerFunctionLibrary.generated.h"

struct FGameplayTag;

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* WeaponData */

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static UDataAsset* GetWeaponData(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static TSubclassOf<AActor> GetActorClass(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static FGameplayTag GetSlotType(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static FName GetActiveSocketName(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static FName GetInActiveSocketName(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static float GetMaxDurability(UObject* DataObject);

    /* WeaponInstance */

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static UObject* GetWeaponInstance(UObject* DataInstance);

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static AActor* GetActor(UObject* DataInstance);

    UFUNCTION(BlueprintCallable, Category = "WeaponInstance")
    static void SetActor(UObject* DataInstance, AActor* NewActor);

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static float GetDurability(UObject* DataInstance);

    UFUNCTION(BlueprintCallable, Category = "WeaponInstance")
    static void SetDurability(UObject* DataInstance, float NewDurability);
};
