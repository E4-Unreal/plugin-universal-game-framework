// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataAssetBase.h"

void UItemDataAssetBase::Update(int32 NewID, FTableRowBase* NewRow)
{
    if (ID != NewID)
    {
        ID = NewID;
        MarkPackageDirty();
    }

    SetData(NewRow);

    bValid = IsValid();
}

void UItemDataAssetBase::SetData(FTableRowBase* NewRow)
{

}
