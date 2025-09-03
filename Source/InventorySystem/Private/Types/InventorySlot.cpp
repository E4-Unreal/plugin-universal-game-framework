// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/InventorySlot.h"

#include "Interfaces/ItemDataInterface.h"

const FInventorySlot FInventorySlot::EmptySlot{ -1, nullptr, -1 };

const int32 FInventorySlot::GetMaxStack() const
{
    return IsValid() ? Item.GetMaxStack() : 0;
}

const int32 FInventorySlot::GetCapacity() const
{
    return IsValid() ? GetMaxStack() - GetQuantity() : 0;
}

FGameplayTag FInventorySlot::GetItemType() const
{
    return IsValid() ? Item.GetItemType() : FGameplayTag::EmptyTag;
}

int32 FInventorySlot::GetQuantity() const
{
    return IsValid() ? Item.Quantity : 0;
}

void FInventorySlot::SetQuantity(int32 NewQuantity)
{
    if (IsValid())
    {
        Item.Quantity = NewQuantity;
    }
}
