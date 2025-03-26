// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UGFInventorySlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UGFInventoryComponent.h"

void UUGFInventorySlotWidget::InitializeInventorySlot(UUGFInventoryComponent* InInventoryComponent, int32 InIndex)
{
    InventoryComponent = InInventoryComponent;
    Index = InIndex;

    Refresh();
}

void UUGFInventorySlotWidget::Refresh()
{
    if (InventoryComponent == nullptr) SetInventorySlot(DefaultInventorySlot);

    const auto& InventorySlot = InventoryComponent->GetInventorySlot(Index);
    if (InventorySlot.Index < 0) SetInventorySlot(DefaultInventorySlot);
    else SetInventorySlot(InventorySlot);
}

void UUGFInventorySlotWidget::SetInventorySlot(const FUGFInventorySlot& InInventorySlot)
{
    if (InInventorySlot.InventoryItemConfig == nullptr) return;

    const auto& Data = InInventorySlot.InventoryItemConfig->GetData();
    if (ThumbnailImage) ThumbnailImage->SetBrushFromSoftTexture(Data.ThumbnailTexture);
    if (QuantityTextBlock) QuantityTextBlock->SetText(FText::FromString(FString::FromInt(InInventorySlot.Quantity)));
}
