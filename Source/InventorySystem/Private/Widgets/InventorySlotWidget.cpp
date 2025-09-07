// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotWidget.h"

#include "Components/TextBlock.h"
#include "Widgets/DraggedInventorySlotWidget.h"

void UInventorySlotWidget::Clear()
{
    Super::Clear();

    SetQuantityTextBlock(0);
}

void UInventorySlotWidget::SetQuantityTextBlock(int32 Quantity)
{
    if (QuantityTextBlock)
    {
        if (Quantity <= 0)
        {
            QuantityTextBlock->SetText(FText::GetEmpty());
        }
        else
        {
            QuantityTextBlock->SetText(FText::FromString(FString::FromInt(Quantity)));
        }
    }
}
