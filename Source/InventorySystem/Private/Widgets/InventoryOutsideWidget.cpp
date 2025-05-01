// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryOutsideWidget.h"

#include "Components/InventoryComponent.h"
#include "Widgets/InventorySlotWidgetBase.h"

void UInventoryOutsideWidget::OnInventorySlotWidgetDrop(UInventorySlotWidgetBase* InventorySlotWidget)
{
    Super::OnInventorySlotWidgetDrop(InventorySlotWidget);

    auto InventoryComponent = InventorySlotWidget->GetInventoryComponent();
    int32 SlotIndex = InventorySlotWidget->GetSlotIndex();
    const auto& InventorySlot = InventoryComponent->GetInventorySlot(SlotIndex);
    InventoryComponent->DropItemFromSlot(SlotIndex, InventorySlot.Quantity);
}
