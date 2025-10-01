// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBuilder.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataDefinitionTableRowBase.h"

TSet<int32> UDataDefinitionBuilder::GetIDSet() const
{
    TSet<int32> IDSet;
    if (!DataTable.IsNull())
    {
        const TArray<FName> RowNames = DataTable.LoadSynchronous()->GetRowNames();
        IDSet.Reserve(RowNames.Num());
        for (const auto& RowName : RowNames)
        {
            int32 ID = ConvertRowNameToID(RowName);
            if (ID < 0) continue;

            IDSet.Emplace(ID);
        }
    }

    return IDSet;
}

FString UDataDefinitionBuilder::GetDataName() const
{
    return DataName.IsNone() && !DefinitionClass.IsNull() ? DefinitionClass.LoadSynchronous()->GetName() : DataName.ToString();
}

FString UDataDefinitionBuilder::GetAssetPath() const
{
    FString AssetPath = FPackageName::GetLongPackagePath(GetPackage()->GetPathName());
    FString DataNameString = GetDataName();
    if (!DataNameString.IsEmpty()) AssetPath += "/" + DataNameString;

    return AssetPath;
}

FString UDataDefinitionBuilder::GetAssetName(int32 ID) const
{
    FString AssetName = Prefix.IsNone() ? GetDataName() : Prefix.ToString() + "_" + GetDataName();
    AssetName += "_" + FString::FromInt(ID);

    if (!DataTable.IsNull())
    {
        auto TableRow = DataTable.LoadSynchronous()->FindRow<FDataDefinitionTableRowBase>(FName(FString::FromInt(ID)), "");
        if (TableRow && !TableRow->DisplayName.IsEmptyOrWhitespace())
        {
            AssetName += "_" + TableRow->DisplayName.ToString();
        }
    }

    return AssetName;
}

bool UDataDefinitionBuilder::UpdateData(UDataDefinitionBase* Definition, int32 ID)
{
    bool bDirty = false;

    if (Definition && ID >= 0)
    {
        if (auto TableRow = DataTable.LoadSynchronous()->FindRow<FDataDefinitionTableRowBase>(FName(FString::FromInt(ID)), ""))
        {
            SET_DATA(Definition->ID, ID)
            SET_TEXT(Definition->DisplayName, TableRow->DisplayName)
            SET_TEXT(Definition->Description, TableRow->Description)

            return OnUpdateData(Definition, TableRow) || bDirty;
        }
    }

    return false;
}

int32 UDataDefinitionBuilder::ConvertRowNameToID(FName RowName)
{
    FString IDString = RowName.ToString();
    if (IDString.IsNumeric())
    {
        int32 ID = FCString::Atoi(*IDString);

        return ID;
    }

    return -1;
}
