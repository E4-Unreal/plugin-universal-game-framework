// Fill out your copyright notice in the Description page of Project Settings.


#include "UGFDefinitionGenerator.h"

#include "Data/DefinitionBase.h"
#include "Types/UGFItemDefinitionDataTableRow.h"

void UUGFDefinitionGenerator::OnUpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row)
{
    if (FUGFItemDefinitionDataTableRow* ItemDefinitionDataTableRow = static_cast<FUGFItemDefinitionDataTableRow*>(Row))
    {
        Definition->SetData(ItemDefinitionDataTableRow->GetInventoryItemData());
    }
}
