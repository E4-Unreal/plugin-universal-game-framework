// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/Flexible/DataFragment.h"
#include "Interfaces/WeaponDataInterface.h"
#include "WeaponDataFragment.generated.h"

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponDataFragment : public UDataFragment, public IWeaponDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayTag SlotType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "WeaponActorInterface"))
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName ActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName InActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float MaxDurability;

public:
    UWeaponDataFragment();

    /* DataFragment */

    virtual UDataInstanceFragment* CreateDataInstanceFragment() const override;

    /* WeaponDataInterface */

    virtual FGameplayTag GetSlotType_Implementation() const override { return SlotType; }
    virtual TSubclassOf<AActor> GetActorClass_Implementation() const override { return ActorClass; }
    virtual FName GetActiveSocketName_Implementation() const override { return ActiveSocketName; }
    virtual FName GetInActiveSocketName_Implementation() const override { return InActiveSocketName; }
    virtual float GetMaxDurability_Implementation() const override { return MaxDurability; }
};
