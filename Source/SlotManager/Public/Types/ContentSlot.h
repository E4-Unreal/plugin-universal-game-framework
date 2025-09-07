// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentSlot.generated.h"

class USlotContent;

USTRUCT(BlueprintType)
struct SLOTMANAGER_API FContentSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USlotContent> Content;
};
