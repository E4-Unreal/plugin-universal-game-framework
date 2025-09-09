// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SlotPanelWidgetBase.h"
#include "InventoryPanelWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventoryPanelWidget : public USlotPanelWidgetBase
{
    GENERATED_BODY()

public:
    UInventoryPanelWidget(const FObjectInitializer& ObjectInitializer);
};
