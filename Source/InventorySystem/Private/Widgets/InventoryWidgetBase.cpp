// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidgetBase.h"

#include "Components/InventoryComponent.h"

void UInventoryWidgetBase::SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
{
    OnInventoryComponentChanged(InventoryComponentPrivate.Get(), NewInventoryComponent);

    InventoryComponentPrivate = NewInventoryComponent;
}

void UInventoryWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindInventoryComponent();
}

void UInventoryWidgetBase::FindInventoryComponent()
{
    if (!InventoryComponentPrivate.IsValid()) FindInventoryComponentFromPlayerPawn();
    if (!InventoryComponentPrivate.IsValid()) FindInventoryComponentFromPlayer();
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
