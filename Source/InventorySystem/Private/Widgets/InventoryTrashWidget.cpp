// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryTrashWidget.h"

void UInventoryTrashWidget::OnWidgetDrop(UUserWidget* DropWidget)
{
    Super::OnWidgetDrop(DropWidget);

    //GetInventoryComponent()->ClearSlot(InventorySlotWidget->GetSlotIndex());
}
