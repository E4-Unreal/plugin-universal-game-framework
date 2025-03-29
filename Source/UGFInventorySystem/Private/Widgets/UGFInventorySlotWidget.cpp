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

void UUGFInventorySlotWidget::SetInventorySlot(const FUGFInventorySlot& InInventorySlot)
{
    if (InInventorySlot.InventoryItemConfig == nullptr)
    {
        Clear();
        return;
    }

    const auto& Data = InInventorySlot.InventoryItemConfig->GetData();
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
