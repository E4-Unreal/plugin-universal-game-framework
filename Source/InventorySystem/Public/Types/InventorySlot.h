// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
    FItemInstance Item;

    FInventorySlot() {}
    FInventorySlot(int32 InIndex, const TScriptInterface<IItemDataInterface>& InData, int32 InQuantity)
    {
        Index = InIndex;
        Item = FItemInstance(InData, InQuantity);
    }

    const int32 GetMaxStack() const;
    const int32 GetCapacity() const;
    FGameplayTag GetItemType() const;
    int32 GetQuantity() const;
    void SetQuantity(int32 NewQuantity);

    FORCEINLINE bool IsValid() const { return Index >= 0 && Item.IsValid(); }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    bool operator==(const FInventorySlot& Other) const { return Index == Other.Index; }
    bool operator!=(const FInventorySlot& Other) const { return !(*this == Other); }
    bool operator<(const FInventorySlot& Other) const { return Index < Other.Index; }
    bool operator>(const FInventorySlot& Other) const { return Index > Other.Index; }

    bool operator==(int32 OtherIndex) const { return Index == OtherIndex; }
    bool operator!=(int32 OtherIndex) const { return !(*this == OtherIndex); }

    bool operator==(const FItemInstance& Other) const { return Item == Other; }
    bool operator!=(const FItemInstance& Other) const { return !(*this == Other); }

    bool operator==(const TScriptInterface<IItemDataInterface>& Other) const { return Item.Data == Other; }
    bool operator!=(const TScriptInterface<IItemDataInterface>& Other) const { return !(*this == Other); }
};
