// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "InventoryTrashWidget.generated.h"

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryTrashWidget : public UInventoryWidgetBase
{
    GENERATED_BODY()

protected:
    virtual void OnInventorySlotWidgetDrop(UInventorySlotWidgetBase* InventorySlotWidget) override;
};
