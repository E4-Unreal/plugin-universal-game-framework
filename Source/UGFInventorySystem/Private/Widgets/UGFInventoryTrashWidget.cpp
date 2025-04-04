// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UGFInventoryTrashWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/UGFInventoryComponent.h"
#include "Widgets/UGFDraggedInventorySlotWidget.h"

void UUGFInventoryTrashWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (auto OwningPawn = GetOwningPlayerPawn())
    {
        InventoryComponent = OwningPawn->GetComponentByClass<UUGFInventoryComponent>();
    }
}

bool UUGFInventoryTrashWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                            UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual)
    {
        if (auto DraggedInventorySlotWidget = Cast<UUGFDraggedInventorySlotWidget>(InOperation->DefaultDragVisual))
        {
            if (InventoryComponent)
            {
                InventoryComponent->ClearInventorySlot(DraggedInventorySlotWidget->SlotIndex);
            }
        }
    }

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
