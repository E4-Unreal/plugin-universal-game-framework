// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DefaultItemDefinition.h"

#include "Types/ActorItemData.h"
#include "Types/DefaultItemDataTableRow.h"

void UDefaultItemDefinition::UpdateDataList(UScriptStruct* RowStruct, FTableRowBase* TableRow)
{
    Super::UpdateDataList(RowStruct, TableRow);

    if (RowStruct->IsChildOf(FDefaultItemDataTableRow::StaticStruct()))
    {
        FDefaultItemDataTableRow* DefaultItemDataTableRow = static_cast<FDefaultItemDataTableRow*>(TableRow);
        UpdateDataList(*DefaultItemDataTableRow);
    }
}

void UDefaultItemDefinition::UpdateDataList(const FDefaultItemDataTableRow& DefaultItemDataTableRow)
{
    FActorItemData ActorItemData;
    ActorItemData.StaticMesh = DefaultItemDataTableRow.StaticMesh;
    SetData(ActorItemData);
}
