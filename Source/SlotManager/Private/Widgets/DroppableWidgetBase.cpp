// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DroppableWidgetBase.h"

#include "Blueprint/DragDropOperation.h"

bool UDroppableWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                        UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual)
    {
        if (UUserWidget* DraggedWidget = Cast<UUserWidget>(InOperation->DefaultDragVisual))
        {
            OnWidgetDrop(DraggedWidget);
        }
    }

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


void UDroppableWidgetBase::OnWidgetDrop(UUserWidget* DropWidget)
{
    // DropWidget 클래스에 따라 이벤트 처리
}
