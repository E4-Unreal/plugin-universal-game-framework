// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

UDataDefinitionBase::UDataDefinitionBase()
{
    DataType = "Data";
}

FPrimaryAssetId UDataDefinitionBase::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(DataType, FName(FString::FromInt(ID)));
}
