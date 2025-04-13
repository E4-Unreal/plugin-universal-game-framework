// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemConfig_Actor.h"

const FItemConfigData_Actor FItemConfigData_Actor::EmptyData;

void UItemConfig_Actor::OnUpdate(FTableRowBase* TableRow)
{
    FItemConfigData_Actor* NewDataPtr = static_cast<FItemConfigData_Actor*>(TableRow);
    if (NewDataPtr == nullptr)
    {
        Reset();
        return;
    }

    if (Data != *NewDataPtr)
    {
        Data = *NewDataPtr;
        MarkPackageDirty();
    }
}

void UItemConfig_Actor::OnReset()
{
    Data = FItemConfigData_Actor::EmptyData;
}
