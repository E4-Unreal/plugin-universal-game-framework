// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataAssetBase.h"

#include "EditorAssetLibrary.h"

void UItemDataAssetBase::Update(FTableRowBase* TableRow)
{
    if (TableRow == nullptr)
    {
        Reset();
        return;
    }

    OnUpdate(TableRow);

    bValid = IsValid();

    UEditorAssetLibrary::SaveAsset(GetPathName());
}

void UItemDataAssetBase::Reset()
{
    OnReset();

    bValid = false;

    UEditorAssetLibrary::SaveAsset(GetPathName());
}

void UItemDataAssetBase::OnUpdate(FTableRowBase* TableRow)
{

}

void UItemDataAssetBase::OnReset()
{
}
