// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentSlotIndex.h"
#include "EquipmentSlot.generated.h"

class UDataInstanceBase;

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlot
{
    GENERATED_BODY()

    const static FEquipmentSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEquipmentSlotIndex Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SocketTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UDataInstanceBase> Equipment;

    FEquipmentSlot() { }

    bool IsEmpty() const { return Equipment == nullptr; }
};
