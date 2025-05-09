// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DefinitionBase.h"

const FInstancedStruct UDefinitionBase::EmptyData;

bool UDefinitionBase::HasData(const UScriptStruct* StructType) const
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

const FInstancedStruct& UDefinitionBase::GetData(const UScriptStruct* StructType) const
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

void UDefinitionBase::SetData(const FInstancedStruct& Value)
{
    const UScriptStruct* StructType = Value.GetScriptStruct();
    for (auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType) && Data != Value)
        {
            Data = Value;
            return;
        }
    }

    DataList.Emplace(Value);
}

FPrimaryAssetId UDefinitionBase::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(GetClass()->GetFName(), FName(FString::FromInt(GetID())));
}
