// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryPanelWidget.h"

#include "Components/InventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Widgets/InventorySlotWidget.h"

void UInventoryPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    CreateSlotWidgets();
}

void UInventoryPanelWidget::OnInventoryComponentChanged(UInventoryComponent* OldInventoryComponent,
    UInventoryComponent* NewInventoryComponent)
{
    Super::OnInventoryComponentChanged(OldInventoryComponent, NewInventoryComponent);

    if (OldInventoryComponent)
    {
        OldInventoryComponent->InventoryUpdated.RemoveDynamic(this, &ThisClass::OnInventoryUpdated);
    }

    if (NewInventoryComponent)
    {
        NewInventoryComponent->InventoryUpdated.AddDynamic(this, &ThisClass::OnInventoryUpdated);
    }
}

void UInventoryPanelWidget::CreateSlotWidgets()
{
    if (bool bCanCreate = InventoryPanel && SlotWidgetClass && SlotWidgetMap.IsEmpty(); !bCanCreate) return;

    auto InventoryComponent = GetInventoryComponent();
    int32 MaxSlotNum = InventoryComponent ? InventoryComponent->GetMaxSlotNum() : PreviewSlotNum;
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        auto SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotWidgetClass);
        SlotWidget->SetInventoryComponent(InventoryComponent);
        SlotWidget->SetSlotIndex(Index);

        int32 SlotColumn = Index % MaxSlotColumn;
        int32 SlotRow = Index / MaxSlotColumn;
        InventoryPanel->AddChildToUniformGrid(SlotWidget, SlotRow, SlotColumn);

        SlotWidgetMap.Emplace(Index, SlotWidget);
    }
}

void UInventoryPanelWidget::OnInventoryUpdated(int32 SlotIndex)
{
    if (SlotWidgetMap.Contains(SlotIndex))
    {
        SlotWidgetMap[SlotIndex]->Refresh();
    }
}
