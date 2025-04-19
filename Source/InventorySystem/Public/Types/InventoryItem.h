// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "Interfaces/InventoryItemDataInterface.h"
#include "InventoryItem.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FInventoryItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IInventoryItemDataInterface> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
    int32 Quantity = 1;

    const FInventoryItemData GetData() const { return Item.GetObject() ? IInventoryItemDataInterface::Execute_GetInventoryItemData(Item.GetObject()) : FInventoryItemData::Empty; }
};
