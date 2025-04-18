// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotWidgetBase.h"

#include "Components/Image.h"
#include "Components/InventoryComponent.h"

void UInventorySlotWidgetBase::SetSlotIndex(int32 NewSlotIndex)
{
    SlotIndex = NewSlotIndex;
    Refresh();
}

void UInventorySlotWidgetBase::Refresh()
{
    Super::Refresh();

    if (GetInventoryComponent())
    {
        if (GetInventoryComponent()->IsSlotEmpty(SlotIndex))
        {
            Clear();
        }
        else
        {
            UpdateInventoryItemData(GetInventoryComponent()->GetInventorySlot(SlotIndex).GetInventoryItemData());
        }
    }
}

void UInventorySlotWidgetBase::UpdateInventoryItemData(const FInventoryItemData& InventoryItemData)
{
    SetThumbnailImage(InventoryItemData.ThumbnailTexture);
}

void UInventorySlotWidgetBase::Clear()
{
    SetThumbnailImage(nullptr);
}

void UInventorySlotWidgetBase::SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture)
{
    if (ThumbnailTexture == nullptr) GetThumbnailImage()->SetBrushFromTexture(nullptr);
    else GetThumbnailImage()->SetBrushFromSoftTexture(ThumbnailTexture);
}
