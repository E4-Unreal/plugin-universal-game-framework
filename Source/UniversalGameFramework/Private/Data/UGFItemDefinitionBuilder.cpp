// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinitionBuilder.h"

#include "Data/UGFEquipmentDefinition.h"
#include "Data/UGFItemDataTableRow.h"

UUGFItemDefinitionBuilder::UUGFItemDefinitionBuilder()
{
    DataClass = UUGFEquipmentDefinition::StaticClass();
    DataName = "Item";
}

bool UUGFItemDefinitionBuilder::UpdateData(UDataAsset* Data, FTableRowBase* TableRow)
{
    bool bDirty = false;

    UUGFEquipmentDefinition* ItemDefinition = Cast<UUGFEquipmentDefinition>(Data);
    FUGFItemDataTableRow* RowData = static_cast<FUGFItemDataTableRow*>(TableRow);
    if (ItemDefinition && RowData)
    {
        // Data
        SET_TEXT(ItemDefinition->DisplayName, RowData->DisplayName)
        SET_TEXT(ItemDefinition->Description, RowData->Description)

        // Slot
        SET_DATA(ItemDefinition->ThumbnailTexture, RowData->ThumbnailTexture)

        // Actor
        SET_DATA(ItemDefinition->StaticMesh, RowData->StaticMesh)
        SET_DATA(ItemDefinition->SkeletalMesh, RowData->SkeletalMesh)

        // Inventory
        SET_DATA(ItemDefinition->MaxStack, RowData->MaxStack)
        SET_DATA(ItemDefinition->ItemType, RowData->ItemType)

        // Product
        SET_DATA(ItemDefinition->CurrencyType, RowData->CurrencyType)
        SET_DATA(ItemDefinition->BuyPrice, RowData->BuyPrice)
        SET_DATA(ItemDefinition->SellPrice, RowData->SellPrice)

        // Equipment
        SET_DATA(ItemDefinition->SlotType, RowData->SlotType)
        SET_DATA(ItemDefinition->ActiveSocketName, RowData->ActiveSocketName)
        SET_DATA(ItemDefinition->InActiveSocketName, RowData->InActiveSocketName)
        SET_DATA(ItemDefinition->MaxDurability, RowData->MaxDurability)
    }

    return bDirty;
}
