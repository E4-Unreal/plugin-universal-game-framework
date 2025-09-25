// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAssetBuilder.h"

FName UDataAssetBuilder::GetDataName() const
{
    return DataName.IsNone() && !DataClass.IsNull() ? FName(DataClass.LoadSynchronous()->GetName()) : DataName;
}
