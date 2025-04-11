// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemDefinitionData.generated.h"

/**
 *
 */
USTRUCT(Atomic, BlueprintType)
struct FItemDefinitionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayText;

    FORCEINLINE bool operator ==(const FItemDefinitionData& Other) const
    {
        return ID == Other.ID && DisplayText.IdenticalTo(Other.DisplayText);
    }

    FORCEINLINE bool operator !=(const FItemDefinitionData& Other) const
    {
        return !(*this == Other);
    }
};
