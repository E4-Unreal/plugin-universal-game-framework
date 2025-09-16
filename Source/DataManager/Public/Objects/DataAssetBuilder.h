// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataAssetBuilder.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class DATAMANAGER_API UDataAssetBuilder : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataDefinitionInterface"))
    TSubclassOf<UDataAsset> DataClass;

public:
    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE TSubclassOf<UDataAsset> GetDataClass() const { return DataClass; }

    virtual bool UpdateData(UDataAsset* Data, FTableRowBase* TableRow) { return false; }
};
