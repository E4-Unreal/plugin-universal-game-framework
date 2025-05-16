// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicData/Public/Data/DefinitionBase.h"
#include "Interfaces/InventoryItemDataInterface.h"
#include "Types/InventoryItemData.h"
#include "UGFItemDefinition.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemDefinition : public UDefinitionBase,
    public IInventoryItemDataInterface
{
    GENERATED_BODY()

public:
    /* InventoryItemDataInterface */

    virtual const FInventoryItemData GetInventoryItemData_Implementation() const override { return GetData<FInventoryItemData>(); }
};
