// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EquipmentSlotIndex.generated.h"

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlotIndex
{
    GENERATED_BODY()

    static const FEquipmentSlotIndex EmptyIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
    int32 Index;

    FEquipmentSlotIndex() { }

    bool IsValid() const { return Type.IsValid(); }

    bool operator==(const FEquipmentSlotIndex& Other) const { return Type == Other.Type; }
    bool operator!=(const FEquipmentSlotIndex& Other) const { return !(*this == Other); }
    friend uint32 GetTypeHash(const FEquipmentSlotIndex& EquipmentSlotIndex) { return FCrc::MemCrc32(&EquipmentSlotIndex, sizeof(FEquipmentSlotIndex)); }
};
