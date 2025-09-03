// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ItemDataInterface.h"
#include "InventorySlot.generated.h"

struct FInventoryItemData;

USTRUCT(Atomic, BlueprintType)
struct INVENTORYSYSTEM_API FInventorySlot
{
    GENERATED_BODY()

    static const FInventorySlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IItemDataInterface> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

    int32 GetCapacity() const;

    FORCEINLINE bool IsValid() const { return Index >= 0 && Item && Quantity > 0 && Item; }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    bool operator==(const FInventorySlot& Other) const { return Index == Other.Index; }
    bool operator!=(const FInventorySlot& Other) const { return !(*this == Other); }
    bool operator<(const FInventorySlot& Other) const { return Index < Other.Index; }
    bool operator>(const FInventorySlot& Other) const { return Index > Other.Index; }

    bool operator==(int32 OtherIndex) const { return Index == OtherIndex; }
    bool operator!=(int32 OtherIndex) const { return !(*this == OtherIndex); }
};
