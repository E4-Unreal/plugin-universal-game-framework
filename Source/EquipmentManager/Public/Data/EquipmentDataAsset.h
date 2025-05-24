// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/EquipmentDataInterface.h"
#include "Types/EquipmentData.h"
#include "EquipmentDataAsset.generated.h"

/**
 *
 */
UCLASS()
class EQUIPMENTMANAGER_API UEquipmentDataAsset : public UPrimaryDataAsset, public IEquipmentDataInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FEquipmentData Data;

public:
    UFUNCTION(BlueprintPure)
    const FEquipmentData& GetData() const { return Data; }

    /* EquipmentDataInterface */

    virtual FGameplayTag GetEquipmentType_Implementation() const override { return Data.EquipmentType; }
    virtual TSubclassOf<AActor> GetActorClass_Implementation() const override { return Data.ActorClass; }
};
