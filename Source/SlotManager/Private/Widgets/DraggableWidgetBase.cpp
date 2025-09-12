// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DraggableWidgetBase.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

FReply UDraggableWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && CanDrag())
    {
        FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        return EventReply.NativeReply;
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UDraggableWidgetBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
    UDragDropOperation*& OutOperation)
{
    if (UUserWidget* DraggedWidget = CreateDraggedWidget())
    {
        UDragDropOperation* DragAndDropOperation = NewObject<UDragDropOperation>(this, UDragDropOperation::StaticClass());
        DragAndDropOperation->DefaultDragVisual = DraggedWidget;

        OutOperation = DragAndDropOperation;
    }
    else
    {
        Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    }
}

bool UDraggableWidgetBase::CanDrag() const
{
    return bCanDrag && DraggedWidgetClass;
}

UUserWidget* UDraggableWidgetBase::CreateDraggedWidget()
{
    UUserWidget* DraggedWidget = nullptr;

    if (DraggedWidgetClass)
    {
        DraggedWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), DraggedWidgetClass);
        OnDraggedWidgetCreated(DraggedWidget);
    }

    return DraggedWidget;
}

void UDraggableWidgetBase::OnDraggedWidgetCreated(UUserWidget* DraggedWidget)
{
    // DraggedWidget 초기화 및 설정
}
