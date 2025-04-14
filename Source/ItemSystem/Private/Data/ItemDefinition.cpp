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

void UItemDefinition::Update(int32 NewID, FTableRowBase* TableRow)
{
    if (ID != NewID)
    {
        ID = NewID;
        MarkPackageDirty();
    }

    if (TableRow == nullptr)
    {
        Reset();
        return;
    }

    OnUpdate(TableRow);

    CheckValid();
}

void UItemDefinition::OnUpdate(FTableRowBase* TableRow)
{
    if (FItemDataTableRow* ItemDataTableRow = static_cast<FItemDataTableRow*>(TableRow))
    {
        if (!DisplayText.IdenticalTo(ItemDataTableRow->DisplayText))
        {
            DisplayText = ItemDataTableRow->DisplayText;
            MarkPackageDirty();
        }
    }

    UpdateDataList(TableRow);
}

void UItemDefinition::UpdateDataList(FTableRowBase* TableRow)
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
