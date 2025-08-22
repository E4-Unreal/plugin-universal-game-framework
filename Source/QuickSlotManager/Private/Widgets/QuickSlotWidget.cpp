// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlotWidget.h"

#include "Components/Image.h"
#include "Components/QuickSlotManagerComponent.h"

void UQuickSlotWidget::SetSlotIndex(int32 NewSlotIndex)
{
    SlotIndex = NewSlotIndex;
    Refresh();
}

void UQuickSlotWidget::Refresh()
{
    if (QuickSlotManager.IsValid())
    {
        if (TScriptInterface<IQuickSlotDataInterface> Data = IQuickSlotManagerInterface::Execute_GetSlotData(QuickSlotManager.Get(), SlotIndex))
        {
            ApplyData(Data);
        }
        else
        {
            Clear();
        }
    }
    else
    {
        ApplyData(PreviewData);
    }
}

void UQuickSlotWidget::Clear()
{
    ThumbnailImage->SetBrushFromTexture(nullptr);
}

void UQuickSlotWidget::ApplyData(const TScriptInterface<IQuickSlotDataInterface>& InData)
{
    if (UObject* DataObject = InData.GetObject())
    {
        ThumbnailImage->SetBrushFromSoftTexture(IQuickSlotDataInterface::Execute_GetThumbnailTexture(DataObject));
    }
}

void UQuickSlotWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    Refresh();
}
