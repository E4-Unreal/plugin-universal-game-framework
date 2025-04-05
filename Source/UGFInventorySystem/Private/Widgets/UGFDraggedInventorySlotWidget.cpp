// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UGFDraggedInventorySlotWidget.h"

#include "Components/Image.h"

void UUGFDraggedInventorySlotWidget::SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture)
{
    if (ThumbnailImage)
    {
        if (ThumbnailTexture == nullptr) ThumbnailImage->SetBrushFromTexture(nullptr);
        else ThumbnailImage->SetBrushFromSoftTexture(ThumbnailTexture);
    }
}
