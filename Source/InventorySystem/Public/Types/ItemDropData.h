// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDropData.generated.h"

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FItemDropData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "ItemDataInterface"))
    TObjectPtr<UDataAsset> ItemData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1))
    float DropChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int32, float> CountChanceMap;
};
