// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

#include "Types/ItemDataTableRow.h"

const FInstancedStruct UItemDefinition::EmptyData;

void UItemDefinition::CheckValid()
{
    bValid = ID >= 0 && !DisplayText.IsEmpty();
}

bool UItemDefinition::HasData(const UScriptStruct* StructType) const
{
    for (const auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType))
        {
            return true;
        }
    }

    return false;
}

const FInstancedStruct& UItemDefinition::GetData(const UScriptStruct* StructType) const
{
    for (const auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType))
        {
            return Data;
        }
    }

    return EmptyData;
}

void UItemDefinition::SetData(const FInstancedStruct& Value)
{
    const UScriptStruct* StructType = Value.GetScriptStruct();
    for (auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType))
        {
            Data = Value;
            return;
        }
    }

    DataList.Emplace(Value);
}

void UItemDefinition::Update(int32 NewID, UScriptStruct* RowStruct, FTableRowBase* TableRow)
{
    if (ID != NewID)
    {
        ID = NewID;
        MarkPackageDirty();
    }

    if (RowStruct == nullptr || TableRow == nullptr)
    {
        Reset();
        return;
    }

    OnUpdate(RowStruct, TableRow);

    CheckValid();
}

void UItemDefinition::OnUpdate(UScriptStruct* RowStruct, FTableRowBase* TableRow)
{
    if (RowStruct->IsChildOf(FItemDataTableRow::StaticStruct()))
    {
        FItemDataTableRow* ItemDataTableRow = static_cast<FItemDataTableRow*>(TableRow);
        if (!DisplayText.IdenticalTo(ItemDataTableRow->DisplayText))
        {
            DisplayText = ItemDataTableRow->DisplayText;
            MarkPackageDirty();
        }
    }

    UpdateDataList(RowStruct, TableRow);
}

void UItemDefinition::UpdateDataList(UScriptStruct* RowStruct, FTableRowBase* TableRow)
{
    // SetData<T>();
}

void UItemDefinition::Reset()
{
    OnReset();

    bValid = false;

    MarkPackageDirty();
}

void UItemDefinition::OnReset()
{
    DisplayText = FText::GetEmpty();
    DataList.Reset();
}
