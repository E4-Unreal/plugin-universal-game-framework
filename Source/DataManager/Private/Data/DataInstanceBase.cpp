// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstanceBase.h"

void UDataInstanceBase::SetData_Implementation(UDataAsset* NewData)
{
    Data = Data && CanCreateFromData(Data->GetClass()) ? NewData : nullptr;
}

bool UDataInstanceBase::CanCreateFromData(TSubclassOf<UDataAsset> DataClass)
{
    return DataClass && DataInterfaceClass && DataClass->ImplementsInterface(DataInterfaceClass);
}
