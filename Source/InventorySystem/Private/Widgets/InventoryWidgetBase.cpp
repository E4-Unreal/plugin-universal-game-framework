// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidgetBase.h"

#include "CommonUIUtils.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/InventoryComponent.h"
#include "Widgets/InventorySlotWidgetBase.h"

void UInventoryWidgetBase::SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
{
    auto OldInventoryComponent = InventoryComponentPrivate.Get();
    if (OldInventoryComponent != NewInventoryComponent)
    {
        OnInventoryComponentChanged(OldInventoryComponent, NewInventoryComponent);
        InventoryComponentPrivate = NewInventoryComponent;
    }
}

void UInventoryWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindInventoryComponent();
}

bool UInventoryWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->DefaultDragVisual)
    {
        if (auto DraggedWidget = Cast<UInventorySlotWidgetBase>(InOperation->DefaultDragVisual))
        {
            OnInventorySlotWidgetDrop(DraggedWidget);
        }
    }

    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryWidgetBase::FindInventoryComponent()
{
    if (!GetInventoryComponent()) FindInventoryComponentFromParentWidget();
    if (!GetInventoryComponent()) FindInventoryComponentFromPlayerPawn();
    if (!GetInventoryComponent()) FindInventoryComponentFromPlayer();
}

void UInventoryWidgetBase::FindInventoryComponentFromParentWidget()
{
    if (UInventoryWidgetBase* ParentWidget = Cast<UInventoryWidgetBase>(CommonUIUtils::GetOwningUserWidget(this)))
    {
        InventoryComponentPrivate = ParentWidget->GetInventoryComponent();
    }
}

void UInventoryWidgetBase::FindInventoryComponentFromPlayer()
{
    if (auto OwningPlayer = GetOwningPlayer())
    {
        auto FoundComponent = OwningPlayer->GetComponentByClass<UInventoryComponent>();
        SetInventoryComponent(FoundComponent);
    }
}

void UInventoryWidgetBase::FindInventoryComponentFromPlayerPawn()
{
    if (auto OwningPlayerPawn = GetOwningPlayerPawn())
    {
        auto FoundComponent = OwningPlayerPawn->GetComponentByClass<UInventoryComponent>();
        SetInventoryComponent(FoundComponent);
    }
}
