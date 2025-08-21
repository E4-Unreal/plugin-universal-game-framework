// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlot/UGFQuickSlotWidget.h"

#include "Components/Image.h"
#include "Components/QuickSlotManagerComponent.h"

void UUGFQuickSlotWidget::SetSlotIndex(int32 NewSlotIndex)
{
    SlotIndex = NewSlotIndex;
    Refresh();
}

void UUGFQuickSlotWidget::Refresh()
{
    if (QuickSlotManager.IsValid())
    {
        const FQuickSlot& QuickSlot = QuickSlotManager->GetSlot(SlotIndex);
        if (QuickSlot.IsValid())
        {
            ApplyData(QuickSlot.Data);
        }
        else
        {
            Clear();
        }
    }
    else
    {
        Clear();
    }
}

void UUGFQuickSlotWidget::Clear()
{
    ThumbnailImage->SetBrushFromTexture(nullptr);
}

void UUGFQuickSlotWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    ApplyData(PreviewData);
}

void UUGFQuickSlotWidget::ApplyData(const TScriptInterface<IQuickSlotDataInterface>& InData)
{
    if (UObject* DataObject = InData.GetObject())
    {
        ThumbnailImage->SetBrushFromSoftTexture(IQuickSlotDataInterface::Execute_GetThumbnailTexture(DataObject));
    }
}
