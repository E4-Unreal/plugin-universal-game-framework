// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentTypeTag.h"
#include "EquipmentSlotIndex.generated.h"

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlotIndex
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEquipmentTypeTag EquipmentType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index = 0;

    bool IsValid() const { return EquipmentType.IsValid() && Index >= 0; }

    bool operator==(const FEquipmentSlotIndex& other) const { return EquipmentType == other.EquipmentType && Index == other.Index; }
    bool operator!=(const FEquipmentSlotIndex& other) const { return !(*this == other); }
};
