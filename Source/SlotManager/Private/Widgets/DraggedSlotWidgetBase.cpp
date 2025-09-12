// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DraggedSlotWidgetBase.h"

#include "Components/Image.h"
#include "Components/SlotManagerComponentBase.h"
#include "Interfaces/SlotDataInterface.h"

UDraggedSlotWidgetBase::UDraggedSlotWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetVisibilityInternal(ESlateVisibility::HitTestInvisible);
}


void UDraggedSlotWidgetBase::SetSlotManager_Implementation(USlotManagerComponentBase* NewSlotManager)
{
    SlotManager = NewSlotManager;
}

void UDraggedSlotWidgetBase::SetSlotIndex_Implementation(int32 NewSlotIndex)
{
    SlotIndex = NewSlotIndex;
    Execute_Refresh(this);
}

void UDraggedSlotWidgetBase::Refresh_Implementation()
{
    if (SlotManager.IsValid())
    {
        if (UDataAsset* Data = SlotManager->GetData(SlotIndex))
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

void UDraggedSlotWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    Execute_Refresh(this);
}

void UDraggedSlotWidgetBase::SetThumbnailTexture(UTexture2D* NewTexture)
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

void UDraggedSlotWidgetBase::Clear()
{
    SetThumbnailTexture(nullptr);
}

void UDraggedSlotWidgetBase::ApplyData(UDataAsset* InData)
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
