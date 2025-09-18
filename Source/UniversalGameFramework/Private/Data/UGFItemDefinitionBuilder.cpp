// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinitionBuilder.h"

#include "Data/UGFEquipmentDefinition.h"
#include "Data/UGFItemDataTableRow.h"

UUGFItemDefinitionBuilder::UUGFItemDefinitionBuilder()
{
    DataClass = UUGFEquipmentDefinition::StaticClass();
}

bool UUGFItemDefinitionBuilder::UpdateData(UDataAsset* Data, FTableRowBase* TableRow)
{
    UUGFEquipmentDefinition* ItemDefinition = Cast<UUGFEquipmentDefinition>(Data);
    FUGFItemDataTableRow* RowData = static_cast<FUGFItemDataTableRow*>(TableRow);
    if (ItemDefinition && RowData)
    {
        // Data
        ItemDefinition->DisplayName = RowData->DisplayName;
        ItemDefinition->Description = RowData->Description;

        // Slot
        ItemDefinition->ThumbnailTexture = RowData->ThumbnailTexture;

        // Actor
        ItemDefinition->StaticMesh = RowData->StaticMesh;
        ItemDefinition->SkeletalMesh = RowData->SkeletalMesh;

        // Inventory
        ItemDefinition->MaxStack = RowData->MaxStack;
        ItemDefinition->ItemType = RowData->ItemType;

        // Product
        ItemDefinition->CurrencyType = RowData->CurrencyType;
        ItemDefinition->BuyPrice = RowData->BuyPrice;
        ItemDefinition->SellPrice = RowData->SellPrice;

        // Equipment
        ItemDefinition->SlotType = RowData->SlotType;
        ItemDefinition->ActiveSocketName = RowData->ActiveSocketName;
        ItemDefinition->InActiveSocketName = RowData->InActiveSocketName;
        ItemDefinition->MaxDurability = RowData->MaxDurability;

        return true;
    }

    return false;
}
