// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DraggedSlotWidgetBase.h"

#include "Components/Image.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/SlotManagerFunctionLibrary.h"
#include "Interfaces/SlotManagerInterface.h"

UDraggedSlotWidgetBase::UDraggedSlotWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetVisibilityInternal(ESlateVisibility::HitTestInvisible);
}


void UDraggedSlotWidgetBase::SetSlotManager_Implementation(UActorComponent* NewSlotManager)
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
        if (auto Data = ISlotManagerInterface::Execute_GetDefinition(SlotManager.Get(), SlotIndex))
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

void UDraggedSlotWidgetBase::SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewTexture)
{
    if (NewTexture)
    {
        ThumbnailImage->SetBrushTintColor(FLinearColor::White);
        ThumbnailImage->SetBrushFromSoftTexture(NewTexture);
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

void UDraggedSlotWidgetBase::ApplyData(UDataDefinitionBase* InData)
{
    if (USlotManagerFunctionLibrary::HasSlotData(InData))
    {
        auto ThumbnailTexture = USlotManagerFunctionLibrary::GetThumbnailTexture(InData);
        if (ThumbnailTexture == nullptr) ThumbnailTexture = DefaultThumbnailTexture;

        SetThumbnailTexture(ThumbnailTexture);
    }
    else
    {
        Clear();
    }
}
