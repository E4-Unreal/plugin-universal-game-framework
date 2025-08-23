// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SlotWidgetBase.h"

#include "Components/Image.h"
#include "Interfaces/SlotManagerInterface.h"
#include "Interfaces/SlotDataInterface.h"

void USlotWidgetBase::SetSlotManager_Implementation(const TScriptInterface<ISlotManagerInterface>& NewSlotManager)
{
    SlotManager = NewSlotManager ? NewSlotManager.GetObject() : nullptr;
}

void USlotWidgetBase::SetSlotIndex_Implementation(int32 NewSlotIndex)
{
    SlotIndex = NewSlotIndex;
    Execute_Refresh(this);
}

void USlotWidgetBase::Refresh_Implementation()
{
    if (SlotManager.IsValid())
    {
        if (TScriptInterface<ISlotDataInterface> Data = ISlotManagerInterface::Execute_GetSlotData(SlotManager.Get(), SlotIndex))
        {
            Execute_ApplyData(this, Data);
        }
        else
        {
            Execute_Clear(this);
        }
    }
    else
    {
        Execute_ApplyData(this, PreviewData);
    }
}

void USlotWidgetBase::Clear_Implementation()
{
    ThumbnailImage->SetBrushFromTexture(nullptr);
}

void USlotWidgetBase::ApplyData_Implementation(const TScriptInterface<ISlotDataInterface>& InData)
{
    if (UObject* DataObject = InData.GetObject())
    {
        ThumbnailImage->SetBrushFromSoftTexture(ISlotDataInterface::Execute_GetThumbnailTexture(DataObject));
    }
}

void USlotWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    Execute_Refresh(this);
}

void USlotWidgetBase::OnDraggedWidgetCreated(UUserWidget* DraggedWidget)
{
    Super::OnDraggedWidgetCreated(DraggedWidget);

    if (DraggedWidget->Implements<USlotWidgetInterface>())
    {
        Execute_SetSlotManager(DraggedWidget, SlotManager.Get());
        Execute_SetSlotIndex(DraggedWidget, SlotIndex);
    }
}
