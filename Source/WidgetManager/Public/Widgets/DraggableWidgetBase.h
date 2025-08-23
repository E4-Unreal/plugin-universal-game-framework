// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API UDraggableWidgetBase : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> DraggedWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bCanDrag = true;

protected:
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    virtual bool CanDrag() const;
    UUserWidget* CreateDraggedWidget();
    virtual void OnDraggedWidgetCreated(UUserWidget* DraggedWidget);
};
