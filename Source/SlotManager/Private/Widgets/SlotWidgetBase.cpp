// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SlotWidgetBase.h"

#include "Components/Image.h"
#include "Components/SlotManagerComponentBase.h"
#include "Interfaces/SlotDataInterface.h"
#include "Objects/SlotContent.h"

void USlotWidgetBase::SetSlotManager_Implementation(USlotManagerComponentBase* NewSlotManager)
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
        if (USlotContent* Content = SlotManager->GetContent(SlotIndex))
        {
            ApplyData(Content->GetData());
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
    return Super::CanDrag() && SlotManager.IsValid() && !SlotManager->IsSlotEmpty(SlotIndex);
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
        USlotManagerComponentBase* Source = Execute_GetSlotManager(DropWidget);
        int32 SourceIndex = Execute_GetSlotIndex(DropWidget);

        if (SlotManager.IsValid())
        {
            SlotManager->SwapContent(Source, SourceIndex, SlotManager.Get(), SlotIndex);
        }
    }
}

void USlotWidgetBase::SetThumbnailTexture(UTexture2D* NewTexture)
{
    if (NewTexture)
    {
        ThumbnailImage->SetBrushTintColor(FLinearColor::White);
        ThumbnailImage->SetBrushFromTexture(NewTexture);
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
    if (InData && InData->Implements<USlotDataInterface>())
    {
        UTexture2D* ThumbnailTexture = ISlotDataInterface::Execute_GetThumbnailTexture(InData).LoadSynchronous();
        if (ThumbnailTexture == nullptr) ThumbnailTexture = DefaultThumbnailTexture.LoadSynchronous();

        SetThumbnailTexture(ThumbnailTexture);
    }
    else
    {
        Clear();
    }
}
