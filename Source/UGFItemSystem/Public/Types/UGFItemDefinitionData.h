// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFItemDefinitionData.generated.h"

class UUGFItemConfig;

/**
 *
 */
USTRUCT(Atomic, BlueprintType)
struct UGFITEMSYSTEM_API FUGFItemDefinitionData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UUGFItemConfig>> ItemConfigs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack = 1;
};
