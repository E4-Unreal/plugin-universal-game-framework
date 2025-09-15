// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataAssetBuilder.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataAssetBuilder : public UObject
{
    GENERATED_BODY()

public:
    /* API */

    virtual TSubclassOf<UDataAsset> GetDataAssetClass() const { return nullptr; }
    virtual UDataAsset* CreateDataAsset(UDataTable* DataTable, int32 ID) { return nullptr; }
    virtual bool UpdateDataAsset(UDataTable* DataTable, int32 ID, UDataAsset* DataAsset) { return false; }
};
