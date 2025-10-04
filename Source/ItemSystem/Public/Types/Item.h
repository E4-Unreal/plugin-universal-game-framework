// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.generated.h"

class UDataDefinitionBase;

USTRUCT(BlueprintType)
struct ITEMSYSTEM_API FItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UDataDefinitionBase> Definition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 Quantity = 1;
};
