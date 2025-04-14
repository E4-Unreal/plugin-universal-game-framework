// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemContainer.generated.h"

class UItemDefinition;

USTRUCT(Atomic, BlueprintType)
struct ITEMSYSTEM_API FItemContainer
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<UItemDefinition> ItemDefinition;

public:
    UItemDefinition* GetItemDefinition();
};
