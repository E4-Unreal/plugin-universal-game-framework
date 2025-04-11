// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

#include "Types/ItemDataTableRow.h"

bool UItemDefinition::Update(int32 ID, FItemDataTableRow* Row)
{
    // 입력 유효성 검사
    if (ID < 0 || Row == nullptr)
    {
        bValid = false;
        return false;
    }

    bValid = true;

    return OnUpdate(ID, Row);
}

bool UItemDefinition::OnUpdate(int32 ID, FItemDataTableRow* Row)
{
    bool bDirty = false;

    // ItemDefinition 업데이트
    FItemDefinitionData NewData
    {
        ID,
        Row->DisplayText
    };

    if (Data != NewData)
    {
        bDirty = true;
        Data = NewData;
    }

    // ItemConfigs 업데이트
    for (auto ItemConfig : ItemConfigs)
    {
        bool bResult = ItemConfig->Update(this, Row);
        bDirty = bDirty || bResult;
    }

    return bDirty;
}

