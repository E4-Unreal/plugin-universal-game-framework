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

bool USlotWidgetBase::CanDrag() const
{
    return Super::CanDrag() && SlotManager.IsValid() && SlotManager->Implements<USlotManagerInterface>() && !ISlotManagerInterface::Execute_IsSlotEmpty(SlotManager.Get(), SlotIndex);
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

void USlotWidgetBase::OnWidgetDrop(UUserWidget* DropWidget)
{
    Super::OnWidgetDrop(DropWidget);

    if (DropWidget->Implements<USlotWidgetInterface>())
    {
        TScriptInterface<ISlotManagerInterface> OtherSlotManager = Execute_GetSlotManager(DropWidget);
        int32 OtherSlotIndex = Execute_GetSlotIndex(DropWidget);

        // TODO 서로 다른 SlotManager 일 경우를 대비하여 Swap 대신 Set으로 대체 필요
        if (SlotManager.Get() == OtherSlotManager.GetObject())
        {
            ISlotManagerInterface::Execute_SwapSlots(SlotManager.Get(), OtherSlotIndex, SlotIndex);
        }
    }
}
