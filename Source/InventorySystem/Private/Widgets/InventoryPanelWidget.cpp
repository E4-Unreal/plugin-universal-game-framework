// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryPanelWidget.h"

#include "Components/InventoryComponent.h"

UInventoryPanelWidget::UInventoryPanelWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SlotManagerClass = UInventoryComponent::StaticClass();
}
