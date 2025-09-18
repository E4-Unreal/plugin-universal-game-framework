// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/ItemDropData.h"
#include "ItemDropConfig.generated.h"

/**
 *
 */
UCLASS(EditInlineNew)
class INVENTORYSYSTEM_API UItemDropConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FItemDropData> DataList;

public:
    UFUNCTION(BlueprintCallable)
    const TArray<FItemDropData>& GetDataList() const { return DataList; }
};
