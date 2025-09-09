// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFItemDefinition.h"
#include "Interfaces/WeaponDataInterface.h"
#include "UGFEquipmentDefinition.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFEquipmentDefinition : public UUGFItemDefinition,
    public IWeaponDataInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SlotType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "WeaponActorInterface"))
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName InActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxDurability;

public:
    UUGFEquipmentDefinition();

    /* WeaponDataInterface */

    virtual FGameplayTag GetSlotType_Implementation() const override { return SlotType; }
    virtual TSubclassOf<AActor> GetActorClass_Implementation() const override { return ActorClass; }
    virtual FName GetActiveSocketName_Implementation() const override { return ActiveSocketName; }
    virtual FName GetInActiveSocketName_Implementation() const override { return InActiveSocketName; }
    virtual float GetMaxDurability_Implementation() const override { return MaxDurability; }
};
