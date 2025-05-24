// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentTypeTag.h"
#include "EquipmentSlot.generated.h"

class IEquipmentInterface;

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlot
{
    GENERATED_BODY()

    const static FEquipmentSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEquipmentTypeTag EquipmentType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Socket;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IEquipmentInterface> Equipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEquipped = false;

    bool IsValid() const { return EquipmentType.IsValid() && Index >= 0; }
    bool IsEmpty() const { return Equipment.GetInterface() == nullptr; }
};
