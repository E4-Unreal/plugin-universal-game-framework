// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/InventorySlot.h"

#include "Interfaces/InventoryItemDataInterface.h"
#include "Types/InventoryItemData.h"

const FInventoryItemData FInventorySlot::GetInventoryItemData() const
{
    if (Item && Item->Implements<UInventoryItemDataInterface>())
    {
        return IInventoryItemDataInterface::Execute_GetInventoryItemData(Item);
    }

    return FInventoryItemData::Empty;
}

int32 FInventorySlot::GetCapacity() const
{
    const auto& InventoryItemData = GetInventoryItemData();

    return InventoryItemData.IsValid() ? InventoryItemData.MaxStack - Quantity : 0;
}
