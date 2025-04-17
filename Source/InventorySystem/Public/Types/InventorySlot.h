// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "InventorySlot.generated.h"

struct FInventoryItemData;

USTRUCT(Atomic, BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UObject> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

    const FInventoryItemData GetInventoryItemData() const;
    int32 GetCapacity() const;

    FORCEINLINE bool IsValid() const { return Index >= 0 && Item && Quantity > 0 && GetInventoryItemData().IsValid(); }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
