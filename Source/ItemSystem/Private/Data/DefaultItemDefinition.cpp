// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DefaultItemDefinition.h"

#include "Data/ItemConfig_Actor.h"
#include "Types/DefaultItemDataTableRow.h"

void UDefaultItemDefinition::UpdateItemConfigs(FTableRowBase* TableRow)
{
    Super::UpdateItemConfigs(TableRow);

    UpdateActorItemConfig(TableRow);
}

void UDefaultItemDefinition::UpdateActorItemConfig(FTableRowBase* TableRow)
{
    if (FDefaultItemDataTableRow* ItemDataTableRow = static_cast<FDefaultItemDataTableRow*>(TableRow))
    {
        FItemConfigData_Actor NewData;
        NewData.StaticMesh = ItemDataTableRow->StaticMesh;

        UItemConfig_Actor* ItemConfig = GetOrCreateItemConfig<UItemConfig_Actor>();
        if (ItemConfig) ItemConfig->Update(&NewData);
    }
}
