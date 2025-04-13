// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataAssetBase.h"

void UItemDataAssetBase::Update(FTableRowBase* TableRow)
{
    if (TableRow == nullptr)
    {
        Reset();
        return;
    }

    OnUpdate(TableRow);

    bValid = IsValid();
}

void UItemDataAssetBase::Reset()
{
    OnReset();

    bValid = false;
}

void UItemDataAssetBase::OnUpdate(FTableRowBase* TableRow)
{

}

void UItemDataAssetBase::OnReset()
{
}
