// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/InventoryComponent.h"
#include "Widgets/DraggedInventorySlotWidget.h"

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && !GetInventoryComponent()->IsSlotEmpty(SlotIndex))
    {
        FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        return EventReply.NativeReply;
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
    UDragDropOperation*& OutOperation)
{
    if (DraggedWidgetClass)
    {
        auto DraggedWidget = CreateWidget<UInventorySlotWidgetBase>(this, DraggedWidgetClass);
        DraggedWidget->SetSlotIndex(SlotIndex);

        auto DragAndDropOperation = NewObject<UDragDropOperation>(this, UDragDropOperation::StaticClass());
        DragAndDropOperation->DefaultDragVisual = DraggedWidget;

        OutOperation = DragAndDropOperation;
    }
    else
    {
        Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    }
}

void UInventorySlotWidget::OnInventorySlotWidgetDrop(UInventorySlotWidgetBase* InventorySlotWidget)
{
    Super::OnInventorySlotWidgetDrop(InventorySlotWidget);

    auto SourceInventoryComponent = InventorySlotWidget->GetInventoryComponent();
    int32 SourceIndex = InventorySlotWidget->GetSlotIndex();
    SourceInventoryComponent->SwapOrFillInventorySlots(SourceIndex, SlotIndex, GetInventoryComponent());
}

void UInventorySlotWidget::UpdateInventorySlot(const FInventorySlot& InventorySlot)
{
    Super::UpdateInventorySlot(InventorySlot);

    SetQuantityTextBlock(InventorySlot.GetQuantity());
}

void UInventorySlotWidget::Clear()
{
    Super::Clear();

    SetQuantityTextBlock(0);
}

void UInventorySlotWidget::SetQuantityTextBlock(int32 Quantity)
{
    if (QuantityTextBlock)
    {
        if (Quantity <= 0)
        {
            QuantityTextBlock->SetText(FText::GetEmpty());
        }
        else
        {
            QuantityTextBlock->SetText(FText::FromString(FString::FromInt(Quantity)));
        }
    }
}
