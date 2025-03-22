// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UGFItemDefinition.h"
#include "UObject/Object.h"
#include "UGFItem.generated.h"

class UUGFItemDefinition;

/**
 *
 */
USTRUCT(BlueprintType)
struct UGFITEMSYSTEM_API FUGFItem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UUGFItemDefinition> ItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 Quantity = 1;

    bool IsValid() const { return ItemDefinition != nullptr && Quantity > 0; }
    bool IsFull() const { return IsValid() ? Quantity >= ItemDefinition->GetMaxStack() : false; }
};
