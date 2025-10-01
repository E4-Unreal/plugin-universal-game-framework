// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinitionBuilder.h"

#include "Data/UGFEquipmentDefinition.h"
#include "Data/UGFItemDataTableRow.h"

UUGFItemDefinitionBuilder::UUGFItemDefinitionBuilder()
{
    DefinitionClass = UUGFEquipmentDefinition::StaticClass();
    DataName = "Item";
}

bool UUGFItemDefinitionBuilder::OnUpdateData(UDataDefinitionBase* Definition, FDataDefinitionTableRowBase* DataDefinitionTableRow)
{
    bool bDirty = false;

    auto ItemDefinition = Cast<UUGFEquipmentDefinition>(Definition);
    auto RowData = static_cast<FUGFItemDataTableRow*>(DataDefinitionTableRow);
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
        SET_DATA(ItemDefinition->Material, RowData->Material)

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
