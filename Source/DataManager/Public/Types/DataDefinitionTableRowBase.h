// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataDefinitionTableRowBase.generated.h"

USTRUCT(BlueprintType)
struct DATAMANAGER_API FDataDefinitionTableRowBase : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = 0))
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = 1))
    FText Description;
};
