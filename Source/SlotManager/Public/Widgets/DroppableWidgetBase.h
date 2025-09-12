// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DroppableWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class SLOTMANAGER_API UDroppableWidgetBase : public UUserWidget
{
    GENERATED_BODY()

protected:
    /* UserWidget */

    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    /* API */

    virtual void OnWidgetDrop(UUserWidget* DropWidget);
};
