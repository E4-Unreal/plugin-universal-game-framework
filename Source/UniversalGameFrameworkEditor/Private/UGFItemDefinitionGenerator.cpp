// Fill out your copyright notice in the Description page of Project Settings.


#include "UGFItemDefinitionGenerator.h"

#include "Data/DefinitionBase.h"
#include "Data/UGFItemDefinition.h"
#include "Types/UGFItemDefinitionDataTableRow.h"

UUGFItemDefinitionGenerator::UUGFItemDefinitionGenerator()
{
    DefinitionClass = UUGFItemDefinition::StaticClass();
}

void UUGFItemDefinitionGenerator::OnUpdateDefinition(UDefinitionBase* Definition, FDefinitionDataTableRow* Row)
{
    if (FUGFItemDefinitionDataTableRow* ItemDefinitionDataTableRow = static_cast<FUGFItemDefinitionDataTableRow*>(Row))
    {
        Definition->SetData(ItemDefinitionDataTableRow->GetInventoryItemData());
    }
}
