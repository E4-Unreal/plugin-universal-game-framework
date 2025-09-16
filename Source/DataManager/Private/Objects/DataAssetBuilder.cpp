// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/DataAssetBuilder.h"

#include "Interfaces/DataDefinitionInterface.h"

bool UDataAssetBuilder::UpdateData(UDataAsset* Data)
{
    if (Data && Data->Implements<UDataDefinitionInterface>())
    {
        const int32 ID = IDataDefinitionInterface::Execute_GetID(Data);
        FTableRowBase* TableRow = DataTable->FindRow<FTableRowBase>(FName(FString::FromInt(ID)), "");

        return OnUpdateData(Data, TableRow);
    }

    return false;
}

bool UDataAssetBuilder::OnUpdateData(UDataAsset* Data, FTableRowBase* TableRow)
{
    return false;
}
