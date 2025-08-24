// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlotPanelWidget.h"

#include "Components/QuickSlotManagerComponent.h"

UQuickSlotPanelWidget::UQuickSlotPanelWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    MaxSlotColumn = 4;
    PreviewSlotNum = 4;
    SlotManagerClass = UQuickSlotManagerComponent::StaticClass();
}
