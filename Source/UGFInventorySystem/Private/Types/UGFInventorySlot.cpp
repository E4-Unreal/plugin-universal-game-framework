// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/UGFInventorySlot.h"

const FUGFInventorySlot FUGFInventorySlot::EmptySlot;

const FUGFInventoryItemData& FUGFInventorySlot::GetInventoryItemData() const
{
    auto InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(ItemDefinition);
    return InventoryItemConfig != nullptr ? InventoryItemConfig->GetData() : FUGFInventoryItemData::EmptyData;
}
