// Fill out your copyright notice in the Description page of Project Settings.


#include "UGFItemDefinitionGenerator.h"

#include "Data/DefinitionBase.h"
#include "Data/UGFItemDefinition.h"
#include "Types/InventoryItem.h"
#include "Types/UGFItemDefinitionDataTableRow.h"

UUGFItemDefinitionGenerator::UUGFItemDefinitionGenerator()
{
    DefinitionClass = UUGFItemDefinition::StaticClass();
}

void UUGFItemDefinitionGenerator::OnUpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row)
{
    if (FUGFItemDefinitionDataTableRow* ItemDefinitionDataTableRow = static_cast<FUGFItemDefinitionDataTableRow*>(Row))
    {
        FInventoryItemData NewInventoryItemData = ItemDefinitionDataTableRow->GetInventoryItemData();

        if (!Definition->HasData<FInventoryItemData>() || Definition->GetData<FInventoryItemData>() != NewInventoryItemData)
        {
            Definition->SetData(ItemDefinitionDataTableRow->GetInventoryItemData());
            Definition->MarkPackageDirty();
        }
    }
}
