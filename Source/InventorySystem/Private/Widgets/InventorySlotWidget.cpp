// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/InventoryComponent.h"
#include "Widgets/DraggedInventorySlotWidget.h"

void UInventorySlotWidget::Refresh()
{
    auto InventoryComponent = GetInventoryComponent();
    if (!InventoryComponent) return;

    FetchInventorySlot(InventoryComponent->GetInventorySlot(Index));
}

void UInventorySlotWidget::SetIndex(int32 NewIndex)
{
    Index = NewIndex;
    Refresh();
}

void UInventorySlotWidget::Clear()
{
    SetThumbnailImage(nullptr);
    SetQuantityTextBlock(0);
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        return EventReply.NativeReply;
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
    UDragDropOperation*& OutOperation)
{
    auto InventoryComponent = GetInventoryComponent();
    const auto& InventorySlot = InventoryComponent->GetInventorySlot(Index);
    if (InventorySlot.IsNotValid()) return;

    if (DraggedWidgetClass)
    {
        auto DraggedWidget = CreateWidget<UDraggedInventorySlotWidget>(this, DraggedWidgetClass);
        if (ThumbnailImage) DraggedWidget->SetThumbnailImage(ThumbnailImage->GetBrush().GetResourceObject());
        DraggedWidget->SlotIndex = Index;

        auto DragAndDropOperation = NewObject<UDragDropOperation>(this, UDragDropOperation::StaticClass());
        DragAndDropOperation->DefaultDragVisual = DraggedWidget;

        OutOperation = DragAndDropOperation;
    }
    else
    {
        Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    }
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual)
    {
        if (auto DraggedInventorySlotWidget = Cast<UDraggedInventorySlotWidget>(InOperation->DefaultDragVisual))
        {
            auto InventoryComponent = GetInventoryComponent();
            if (InventoryComponent)
            {
                InventoryComponent->SwapOrFillInventorySlots(DraggedInventorySlotWidget->SlotIndex, Index);
            }
        }
    }

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventorySlotWidget::FetchInventorySlot(const FInventorySlot& InventorySlot)
{
    if (InventorySlot.IsNotValid())
    {
        Clear();
        return;
    }

    const auto& InventoryItemData = InventorySlot.GetInventoryItemData();
    SetThumbnailImage(InventoryItemData.ThumbnailTexture);
    SetQuantityTextBlock(InventorySlot.Quantity);
}

void UInventorySlotWidget::SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture)
{
    if (ThumbnailImage)
    {
        if (ThumbnailTexture == nullptr) ThumbnailImage->SetBrushFromTexture(nullptr);
        else ThumbnailImage->SetBrushFromSoftTexture(ThumbnailTexture);
    }
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
