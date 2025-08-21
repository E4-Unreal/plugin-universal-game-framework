// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlot/UGFQuickSlotPanelWidget.h"

#include "Components/QuickSlotManagerComponent.h"
#include "Components/UniformGridPanel.h"
#include "Widgets/QuickSlot/UGFQuickSlotWidget.h"

void UUGFQuickSlotPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    CreateSlotWidgets();
}

void UUGFQuickSlotPanelWidget::CreateSlotWidgets()
{
    // Destroy
    for (int32 Index = 0; Index < SlotWidgetMap.Num(); ++Index)
    {
        UUGFQuickSlotWidget* SlotWidget = SlotWidgetMap[Index];
        SlotWidget->RemoveFromParent();
        QuickSlotPanel->RemoveChildAt(Index);
    }
    SlotWidgetMap.Reset();

    // Create
    int32 SlotNum = QuickSlotManager.IsValid() ? QuickSlotManager->SlotNum : PreviewSlotNum;
    for (int32 Index = 0; Index < SlotNum; ++Index)
    {
        auto SlotWidget = CreateWidget<UUGFQuickSlotWidget>(this, SlotWidgetClass);
        SlotWidget->SetSlotIndex(Index);

        int32 SlotColumn = Index % MaxSlotColumn;
        int32 SlotRow = Index / MaxSlotColumn;
        QuickSlotPanel->AddChildToUniformGrid(SlotWidget, SlotRow, SlotColumn);

        SlotWidgetMap.Emplace(Index, SlotWidget);
    }
}
