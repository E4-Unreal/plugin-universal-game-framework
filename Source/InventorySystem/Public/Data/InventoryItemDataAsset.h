// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/InventoryItemDataInterface.h"
#include "Types/InventoryItemData.h"
#include "InventoryItemDataAsset.generated.h"

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryItemDataAsset : public UPrimaryDataAsset, public IInventoryItemDataInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (ShowOnlyInnerProperties))
    FInventoryItemData InventoryItemData;

public:
    /* InventoryItemDataInterface */

    virtual const FInventoryItemData GetInventoryItemData_Implementation() const override { return InventoryItemData; }
};
