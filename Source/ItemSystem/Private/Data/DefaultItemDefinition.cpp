// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DefaultItemDefinition.h"

#include "Data/ItemConfig_Actor.h"
#include "Types/DefaultItemDataTableRow.h"

void UDefaultItemDefinition::UpdateDataList(FTableRowBase* TableRow)
{
    Super::UpdateDataList(TableRow);

    if (FDefaultItemDataTableRow* DefaultItemDataTableRow = static_cast<FDefaultItemDataTableRow*>(TableRow))
    {
        UpdateDataList(*DefaultItemDataTableRow);
    }
}

void UDefaultItemDefinition::UpdateDataList(const FDefaultItemDataTableRow& DefaultItemDataTableRow)
{
    FItemConfigData_Actor ActorItemData;
    ActorItemData.StaticMesh = DefaultItemDataTableRow.StaticMesh;
    SetData(ActorItemData);
}
