// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryOutsideWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/InventoryComponent.h"
#include "FunctionLibraries/InventorySystemFunctionLibrary.h"
#include "Interfaces/SlotManagerInterface.h"
#include "Widgets/SlotWidgetBase.h"

void UInventoryOutsideWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    ESlateVisibility NewVisibility = UWidgetBlueprintLibrary::IsDragDropping() ? ESlateVisibility::Visible : ESlateVisibility::HitTestInvisible;
    SetVisibility(NewVisibility);
}

void UInventoryOutsideWidget::OnWidgetDrop(UUserWidget* DropWidget)
{
    if (DropWidget && DropWidget->Implements<USlotWidgetInterface>())
    {
        auto SlotManager = ISlotWidgetInterface::Execute_GetSlotManager(DropWidget);
        const int32 SlotIndex = ISlotWidgetInterface::Execute_GetSlotIndex(DropWidget);
        auto SlotContent = ISlotManagerInterface::Execute_GetDataInstance(SlotManager, SlotIndex);

        if (UInventoryComponent* Inventory = Cast<UInventoryComponent>(SlotManager))
        {
            const int32 SlotQuantity = UItemDataFunctionLibrary::GetQuantity(SlotContent);
            Inventory->DropItemFromSlot(SlotIndex, SlotQuantity);
        }
    }
}
