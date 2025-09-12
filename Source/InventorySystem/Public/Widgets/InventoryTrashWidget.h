// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DroppableWidgetBase.h"
#include "InventoryTrashWidget.generated.h"

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryTrashWidget : public UDroppableWidgetBase
{
    GENERATED_BODY()

protected:
    /* DroppableWidgetBase */

    virtual void OnWidgetDrop(UUserWidget* DropWidget) override;
};
