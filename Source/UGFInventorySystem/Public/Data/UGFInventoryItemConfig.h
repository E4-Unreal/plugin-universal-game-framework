// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UGFItemConfig.h"
#include "Types/UGFInventoryItemData.h"
#include "UGFInventoryItemConfig.generated.h"

class UUGFItemDefinition;

/**
 * ItemConfig For UGFInventoryComponent
 */
UCLASS()
class UGFINVENTORYSYSTEM_API UUGFInventoryItemConfig : public UUGFItemConfig
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    FUGFInventoryItemData Data;

public:
    UFUNCTION(BlueprintPure)
    static UUGFInventoryItemConfig* GetFromItemDefinition(const UUGFItemDefinition* ItemDefinition);

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FUGFInventoryItemData& GetData() const { return Data; }
};
