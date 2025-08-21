// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlotPanelWidget.h"

#include "Components/QuickSlotManagerComponent.h"
#include "Components/UniformGridPanel.h"
#include "Widgets/QuickSlotWidget.h"

void UQuickSlotPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    CreateSlotWidgets();
}

void UQuickSlotPanelWidget::ClearSlotWidgets()
{
    for (int32 Index = 0; Index < SlotWidgetMap.Num(); ++Index)
    {
        UQuickSlotWidget* SlotWidget = SlotWidgetMap[Index];
        SlotWidget->RemoveFromParent();
        QuickSlotPanel->RemoveChildAt(Index);
    }
    SlotWidgetMap.Reset();
}

void UQuickSlotPanelWidget::CreateSlotWidgets()
{
    ClearSlotWidgets();

    int32 SlotNum = QuickSlotManager.IsValid() ? QuickSlotManager->SlotNum : PreviewSlotNum;
    for (int32 Index = 0; Index < SlotNum; ++Index)
    {
        UQuickSlotWidget* SlotWidget = CreateWidget<UQuickSlotWidget>(this, SlotWidgetClass);
        SlotWidget->SetSlotIndex(Index);

        int32 SlotColumn = Index % MaxSlotColumn;
        int32 SlotRow = Index / MaxSlotColumn;
        QuickSlotPanel->AddChildToUniformGrid(SlotWidget, SlotRow, SlotColumn);

        SlotWidgetMap.Emplace(Index, SlotWidget);
    }
}
