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
            UpdateInventorySlot(GetInventoryComponent()->GetInventorySlot(SlotIndex));
        }
    }
}

void UInventorySlotWidgetBase::UpdateInventorySlot(const FInventorySlot& InventorySlot)
{
    SetThumbnailImage(IItemDataInterface::Execute_GetThumbnailTexture(InventorySlot.Item.Data.GetObject()));
}

void UInventorySlotWidgetBase::Clear()
{
    GetThumbnailImage()->SetBrushTintColor(FLinearColor::Transparent);
}

void UInventorySlotWidgetBase::SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture)
{
    if (!ThumbnailTexture.IsNull())
    {
        GetThumbnailImage()->SetBrushFromTexture(ThumbnailTexture.LoadSynchronous());
        GetThumbnailImage()->SetBrushTintColor(FLinearColor::White);
    }
}
