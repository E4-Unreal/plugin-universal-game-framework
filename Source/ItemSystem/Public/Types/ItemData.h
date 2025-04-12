// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemData.generated.h"

class UItemDefinition;

USTRUCT(Atomic, BlueprintType)
struct ITEMSYSTEM_API FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UItemDefinition> ItemDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;
};
