// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UGFInventorySlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UGFInventoryComponent.h"
#include "Widgets/UGFDraggedInventorySlotWidget.h"

void UUGFInventorySlotWidget::InitializeInventorySlot(UUGFInventoryComponent* InInventoryComponent, int32 InIndex)
{
    InventoryComponent = InInventoryComponent;
    Index = InIndex;

    Refresh();
}

void UUGFInventorySlotWidget::Refresh()
{
    if (InventoryComponent == nullptr) return;

    const auto& InventorySlot = InventoryComponent->GetInventorySlot(Index);
    if (InventorySlot.IsValid())
    {
        SetInventorySlot(InventorySlot);
    }
    else
    {
        Clear();
    }
}

void UUGFInventorySlotWidget::Clear()
{
    SetThumbnailImage(nullptr);
    SetQuantityTextBlock(0);
}

FReply UUGFInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        FEventReply EventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        return EventReply.NativeReply;
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UUGFInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
    UDragDropOperation*& OutOperation)
{
    if (DraggedWidgetClass)
    {
        auto DraggedWidget = CreateWidget<UUGFDraggedInventorySlotWidget>(this, DraggedWidgetClass);
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

bool UUGFInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual)
    {
        if (auto DraggedInventorySlotWidget = Cast<UUGFDraggedInventorySlotWidget>(InOperation->DefaultDragVisual))
        {
            if (InventoryComponent)
            {
                InventoryComponent->SwapInventorySlot(DraggedInventorySlotWidget->SlotIndex, Index);
            }
        }
    }

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UUGFInventorySlotWidget::SetInventorySlot(const FUGFInventorySlot& InInventorySlot)
{
    if (!InInventorySlot.IsValid())
    {
        Clear();
        return;
    }

    const auto& Data = InInventorySlot.GetInventoryItemData();
    SetThumbnailImage(Data.ThumbnailTexture);
    SetQuantityTextBlock(InInventorySlot.Quantity);
}

void UUGFInventorySlotWidget::SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture)
{
    if (ThumbnailImage)
    {
        if (ThumbnailTexture == nullptr) ThumbnailImage->SetBrushFromTexture(nullptr);
        else ThumbnailImage->SetBrushFromSoftTexture(ThumbnailTexture);
    }
}

void UUGFInventorySlotWidget::SetQuantityTextBlock(int32 Quantity)
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
