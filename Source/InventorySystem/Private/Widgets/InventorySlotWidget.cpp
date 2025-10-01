// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotWidget.h"

#include "Components/TextBlock.h"
#include "FunctionLibraries/InventorySystemFunctionLibrary.h"
#include "Interfaces/SlotManagerInterface.h"

void UInventorySlotWidget::Refresh_Implementation()
{
    Super::Refresh_Implementation();

    if (SlotManager.IsValid())
    {
        auto Content = ISlotManagerInterface::Execute_GetDataInstance(SlotManager.Get(), SlotIndex);
        const int32 Quantity = UInventorySystemFunctionLibrary::GetQuantity(Content);
        SetQuantityTextBlock(Quantity);
    }
}

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
