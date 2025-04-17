// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UObject> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity;
};
