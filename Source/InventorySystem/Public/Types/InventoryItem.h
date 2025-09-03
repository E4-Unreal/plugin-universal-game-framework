// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ItemDataInterface.h"
#include "InventoryItem.generated.h"

USTRUCT(Atomic, BlueprintType)
struct INVENTORYSYSTEM_API FInventoryItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IItemDataInterface> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
    int32 Quantity = 1;

    bool IsValid() const { return Item && Quantity > 0; }
};
