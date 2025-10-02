// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponDataFunctionLibrary.generated.h"

class UDataDefinitionBase;
class UDataInstanceBase;
struct FGameplayTag;

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponDataFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* WeaponData */

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static bool HasWeaponData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static TSubclassOf<AActor> GetActorClass(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static FGameplayTag GetSlotType(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static FName GetActiveSocketName(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static FName GetInActiveSocketName(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "WeaponData")
    static float GetMaxDurability(UDataDefinitionBase* Definition);

    /* WeaponInstance */

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static UDataInstanceBase* CreateItemInstance(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static bool HasWeaponInstance(UDataInstanceBase* Instance);

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static AActor* GetActor(UDataInstanceBase* Instance);

    UFUNCTION(BlueprintCallable, Category = "WeaponInstance")
    static void SetActor(UDataInstanceBase* Instance, AActor* NewActor);

    UFUNCTION(BlueprintPure, Category = "WeaponInstance")
    static float GetDurability(UDataInstanceBase* Instance);

    UFUNCTION(BlueprintCallable, Category = "WeaponInstance")
    static void SetDurability(UDataInstanceBase* Instance, float NewDurability);

protected:
    static UDataAsset* GetWeaponData(UDataDefinitionBase* Definition);
    static UObject* GetWeaponInstance(UDataInstanceBase* Instance);
};
