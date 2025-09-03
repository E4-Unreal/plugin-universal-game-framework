// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/InventorySlot.h"

#include "Interfaces/ItemDataInterface.h"

const FInventorySlot FInventorySlot::EmptySlot{ -1, nullptr, -1 };

int32 FInventorySlot::GetMaxStack() const
{
    return IsValid() ? IItemDataInterface::Execute_GetMaxStack(Item.GetObject()) : 0;
}

int32 FInventorySlot::GetCapacity() const
{
    return IsValid() ? GetMaxStack() - Quantity : 0;
}

FGameplayTag FInventorySlot::GetItemType() const
{
    return IsValid() ? IItemDataInterface::Execute_GetItemType(Item.GetObject()) : FGameplayTag::EmptyTag;
}
