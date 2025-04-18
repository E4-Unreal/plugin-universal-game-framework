// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/InventorySlot.h"

#include "Interfaces/InventoryItemDataInterface.h"
#include "Types/InventoryItemData.h"

const FInventorySlot FInventorySlot::EmptySlot{ -1, nullptr, -1 };

const FInventoryItemData FInventorySlot::GetInventoryItemData() const
{
    return Item ? IInventoryItemDataInterface::Execute_GetInventoryItemData(Item.GetObject()) : FInventoryItemData::Empty;
}

int32 FInventorySlot::GetCapacity() const
{
    const auto& InventoryItemData = GetInventoryItemData();

    return InventoryItemData.IsValid() ? InventoryItemData.MaxStack - Quantity : 0;
}
