// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UGFInventoryItemConfig.h"
#include "UObject/Object.h"
#include "UGFInventorySlot.generated.h"

class UUGFInventoryItemConfig;
class UUGFItemDefinition;

/**
 *
 */
USTRUCT(BlueprintType)
struct UGFINVENTORYSYSTEM_API FUGFInventorySlot
{
    GENERATED_BODY()

public:
    static const FUGFInventorySlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UUGFItemDefinition> ItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = -1;

public:
    FUGFInventorySlot() {}

    const FUGFInventoryItemData& GetInventoryItemData() const;

    bool IsValid() const { return Index >= 0 && ItemDefinition != nullptr && Quantity > 0; }
};
