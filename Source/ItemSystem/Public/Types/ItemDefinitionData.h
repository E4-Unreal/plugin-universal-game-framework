// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemDefinitionData.generated.h"

/**
 * ItemDefinition 데이터 에셋 전용 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FItemDefinitionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayText;

    static const FItemDefinitionData EmptyData;

    bool IsValid() const { return !DisplayText.IsEmpty(); }

    bool IsNotValid() const { return !IsValid(); }

    FORCEINLINE bool operator ==(const FItemDefinitionData& Other) const
    {
        return DisplayText.IdenticalTo(Other.DisplayText);
    }

    FORCEINLINE bool operator !=(const FItemDefinitionData& Other) const
    {
        return !(*this == Other);
    }
};
