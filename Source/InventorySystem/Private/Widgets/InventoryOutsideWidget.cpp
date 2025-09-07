// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryOutsideWidget.h"

#include "Components/InventoryComponent.h"
#include "Interfaces/ItemInstanceInterface.h"
#include "Objects/SlotContent.h"
#include "Widgets/InventorySlotWidgetBase.h"
#include "Widgets/SlotWidgetBase.h"

void UInventoryOutsideWidget::OnWidgetDrop(UUserWidget* DropWidget)
{
    if (DropWidget && DropWidget->Implements<USlotWidgetInterface>())
    {
        if (UInventoryComponent* Inventory = Cast<UInventoryComponent>(ISlotWidgetInterface::Execute_GetSlotManager(DropWidget)))
        {
            const int32 SlotIndex = ISlotWidgetInterface::Execute_GetSlotIndex(DropWidget);
            const int32 SlotQuantity = IItemInstanceInterface::Execute_GetQuantity(Inventory->GetContent(SlotIndex));

            Inventory->DropItemFromSlot(SlotIndex, SlotQuantity);
        }
    }
}
