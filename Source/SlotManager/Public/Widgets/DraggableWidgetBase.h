// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroppableWidgetBase.h"
#include "DraggableWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class SLOTMANAGER_API UDraggableWidgetBase : public UDroppableWidgetBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> DraggedWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bCanDrag = true;

protected:
    /* UserWidget */

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    /* API */

    virtual bool CanDrag() const;
    UUserWidget* CreateDraggedWidget();
    virtual void OnDraggedWidgetCreated(UUserWidget* DraggedWidget);
};
