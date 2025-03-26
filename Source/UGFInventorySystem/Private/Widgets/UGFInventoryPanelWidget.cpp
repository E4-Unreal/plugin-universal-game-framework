// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UGFInventoryPanelWidget.h"

#include "Components/UGFInventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Widgets/UGFInventorySlotWidget.h"

void UUGFInventoryPanelWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (auto OwningPlayer = GetOwningPlayerPawn())
    {
        InventoryComponent = OwningPlayer->GetComponentByClass<UUGFInventoryComponent>();
    }
}

void UUGFInventoryPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    CreateSlotWidgets();
}

void UUGFInventoryPanelWidget::CreateSlotWidgets()
{
    if (InventoryPanel == nullptr) return;

    int32 MaxSlotNum = InventoryComponent != nullptr ? InventoryComponent->GetMaxSlotNum() : PreviewSlotNum;
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        auto SlotWidget = CreateWidget<UUGFInventorySlotWidget>(this, SlotWidgetClass);
        SlotWidget->InitializeInventorySlot(InventoryComponent, Index);

        int32 SlotColumn = Index % MaxSlotColumn;
        int32 SlotRow = Index / MaxSlotColumn;
        InventoryPanel->AddChildToUniformGrid(SlotWidget, SlotRow, SlotColumn);
    }
}
