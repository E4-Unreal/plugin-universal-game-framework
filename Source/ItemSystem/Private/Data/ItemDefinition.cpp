// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

#include "Types/ItemDataTableRow.h"

bool UItemDefinition::Update(int32 ID, FItemDataTableRow* Row, const TArray<TSubclassOf<UItemConfig>>& ItemConfigClasses)
{
    // 입력 유효성 검사
    if (ID < 0 || Row == nullptr)
    {
        bValid = false;
        return false;
    }

    // ItemConfig 생성
    for (auto ItemConfigClass : ItemConfigClasses)
    {
        FName NewItemConfigName = FName(ItemConfigClass->GetName() + FString("_") + FString::FromInt(ID));
        auto NewItemConfig = NewObject<UItemConfig>(this, ItemConfigClass, NewItemConfigName);
        ItemConfigs.Emplace(NewItemConfig);
    }
    GetPackage()->MarkPackageDirty();

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

