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
    // 데이터 생성
    FItemDefinitionData NewData
    {
        ID,
        Row->DisplayText
    };

    // 데이터 비교
    if (Data == NewData) return false;
    Data = NewData;

    return true;
}

