// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UGFInventoryOutsideWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/UGFInventoryComponent.h"
#include "Widgets/UGFDraggedInventorySlotWidget.h"

void UUGFInventoryOutsideWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (auto OwningPawn = GetOwningPlayerPawn())
    {
        InventoryComponent = OwningPawn->GetComponentByClass<UUGFInventoryComponent>();
    }
}

bool UUGFInventoryOutsideWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                              UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual)
    {
        if (auto DraggedInventorySlotWidget = Cast<UUGFDraggedInventorySlotWidget>(InOperation->DefaultDragVisual))
        {
            if (InventoryComponent)
            {
                const auto& InventorySlot = InventoryComponent->GetInventorySlot(DraggedInventorySlotWidget->SlotIndex);
                InventoryComponent->DropItemFromSlot(InventorySlot.Index, InventorySlot.Quantity);
            }
        }
    }

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
