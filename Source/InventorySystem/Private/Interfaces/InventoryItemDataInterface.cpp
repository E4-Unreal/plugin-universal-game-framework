// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InventoryItemDataInterface.h"

#include "Logging.h"
#include "Types/InventoryItemData.h"


// Add default functionality here for any IInventoryItemDataInterface functions that are not pure virtual.
const FInventoryItemData& IInventoryItemDataInterface::GetInventoryItemData_Implementation() const
{
    LOG_TODO_INTERFACE

    return FInventoryItemData::Empty;
}
