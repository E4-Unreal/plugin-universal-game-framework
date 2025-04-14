// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemContainer.generated.h"

class UItemDefinition;

USTRUCT(Atomic, BlueprintType)
struct ITEMSYSTEM_API FItemContainer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UItemDefinition> ItemDefinition;

    UItemDefinition* GetItemDefinition() const;

    FORCEINLINE bool IsValid() const { return Quantity > 0 && GetItemDefinition() != nullptr; }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
