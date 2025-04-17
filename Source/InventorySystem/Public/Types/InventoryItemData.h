// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItemData.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FInventoryItemData
{
    GENERATED_BODY()

    static const FInventoryItemData Empty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanEquip = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanUse = false;

    FORCEINLINE bool IsValid() const { return MaxStack > 0; }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
