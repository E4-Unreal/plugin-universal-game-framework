// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentSlotIndex.h"
#include "EquipmentSlot.generated.h"

class IEquipmentActorInterface;

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlot
{
    GENERATED_BODY()

    const static FEquipmentSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEquipmentSlotIndex SlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Socket;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IEquipmentActorInterface> Equipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEquipped = false;

    bool IsValid() const { return SlotIndex.EquipmentType.IsValid() && SlotIndex.Index >= 0; }
    bool IsEmpty() const { return Equipment.GetInterface() == nullptr; }
};
