// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UGFItemConfig.h"
#include "UGFInventoryItemConfig.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FUGInventoryItemConfigData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack = 1;
};

class UUGFItemDefinition;

/**
 * ItemConfig For UGFInventoryComponent
 */
UCLASS()
class UGFINVENTORYSYSTEM_API UUGFInventoryItemConfig : public UUGFItemConfig
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    FUGInventoryItemConfigData Data;

public:
    UFUNCTION(BlueprintPure)
    static UUGFInventoryItemConfig* GetFromItemDefinition(const UUGFItemDefinition* ItemDefinition);

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FUGInventoryItemConfigData& GetData() const { return Data; }
};
