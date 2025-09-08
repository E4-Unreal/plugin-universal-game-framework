// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "WeaponDataInterface.generated.h"

class USlotContent;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UWeaponDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WEAPONMANAGER_API IWeaponDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSubclassOf<AActor> GetActorClass() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetSlotType() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FName GetActiveSocketName() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FName GetInActiveSocketName() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UStaticMesh> GetStaticMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetMaxDurability() const;
};
