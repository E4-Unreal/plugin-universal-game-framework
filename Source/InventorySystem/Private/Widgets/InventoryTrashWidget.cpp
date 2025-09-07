// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryTrashWidget.h"

#include "Components/InventoryComponent.h"
#include "Widgets/InventorySlotWidgetBase.h"

void UInventoryTrashWidget::OnInventorySlotWidgetDrop(UInventorySlotWidgetBase* InventorySlotWidget)
{
    Super::OnInventorySlotWidgetDrop(InventorySlotWidget);

    //GetInventoryComponent()->RemoveInventorySlot(InventorySlotWidget->GetSlotIndex());
}
