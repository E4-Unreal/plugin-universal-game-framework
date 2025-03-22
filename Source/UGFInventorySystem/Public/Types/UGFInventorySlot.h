// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UUGFItemDefinition> ItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 Quantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UUGFInventoryItemConfig> InventoryItemConfig;
};
