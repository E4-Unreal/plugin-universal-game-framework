// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentTypeTag.h"
#include "EquipmentSlot.generated.h"

class IEquipmentActorInterface;

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlot
{
    GENERATED_BODY()

    const static FEquipmentSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEquipmentTypeTag EquipmentType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Socket"))
    FGameplayTag Socket;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Equipment;

    bool IsValid() const { return EquipmentType.IsValid() && Index >= 0; }
    bool IsEmpty() const { return Equipment == nullptr; }
};
