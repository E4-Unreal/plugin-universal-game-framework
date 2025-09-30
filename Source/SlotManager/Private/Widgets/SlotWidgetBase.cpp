// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SlotWidgetBase.h"

#include "Components/Image.h"
#include "FunctionLibraries/SlotManagerFunctionLibrary.h"
#include "Interfaces/SlotManagerInterface.h"

void USlotWidgetBase::SetSlotManager_Implementation(UActorComponent* NewSlotManager)
{
    SlotManager = NewSlotManager;
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
        if (auto Data = ISlotManagerInterface::Execute_GetData(SlotManager.Get(), SlotIndex))
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
        ApplyData(PreviewData.LoadSynchronous());
    }
}

void USlotWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    Execute_Refresh(this);
}

bool USlotWidgetBase::CanDrag() const
{
    return Super::CanDrag() && SlotManager.IsValid() && !ISlotManagerInterface::Execute_IsSlotEmpty(SlotManager.Get(), SlotIndex);
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
        auto Source = Execute_GetSlotManager(DropWidget);
        int32 SourceIndex = Execute_GetSlotIndex(DropWidget);

        if (SlotManager.IsValid())
        {
            ISlotManagerInterface::Execute_SwapSlots(SlotManager.Get(), Source, SourceIndex, SlotManager.Get(), SlotIndex);
        }
    }
}

void USlotWidgetBase::SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewTexture)
{
    if (!NewTexture.IsNull())
    {
        ThumbnailImage->SetBrushTintColor(FLinearColor::White);
        ThumbnailImage->SetBrushFromSoftTexture(NewTexture);
    }
    else
    {
        ThumbnailImage->SetBrushTintColor(FLinearColor::Transparent);
    }
}

void USlotWidgetBase::Clear()
{
    SetThumbnailTexture(nullptr);
}

void USlotWidgetBase::ApplyData(UDataAsset* InData)
{
    auto ThumbnailTexture = USlotManagerFunctionLibrary::GetThumbnailTexture(InData);
    if (ThumbnailTexture.IsNull()) ThumbnailTexture = DefaultThumbnailTexture;


    SetThumbnailTexture(ThumbnailTexture);
}
