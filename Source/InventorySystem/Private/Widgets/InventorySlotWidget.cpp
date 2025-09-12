// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotWidget.h"

#include "Components/SlotManagerComponentBase.h"
#include "Components/TextBlock.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemInstanceInterface.h"

void UInventorySlotWidget::Refresh_Implementation()
{
    Super::Refresh_Implementation();

    if (SlotManager.IsValid())
    {
        auto Content = SlotManager->GetContent(SlotIndex);
        if (Content && Content->Implements<UItemInstanceInterface>())
        {
            const int32 Quantity = IItemInstanceInterface::Execute_GetQuantity(Content);
            SetQuantityTextBlock(Quantity);
        }
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
