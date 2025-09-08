// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataSlot.generated.h"

class UDataCollection;
class UDataInstanceBase;

USTRUCT(BlueprintType)
struct SLOTMANAGER_API FDataSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UDataCollection> Collection;
};
