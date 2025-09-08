// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstanceBase.h"

void UDataInstanceBase::SetData_Implementation(UDataAsset* NewData)
{
    Data = Data && CanBeCreatedFromData(Data) ? NewData : nullptr;
}

bool UDataInstanceBase::CanBeCreatedFromData_Implementation(UDataAsset* InData) const
{
    return InData && DataInterfaceClass && InData->GetClass()->ImplementsInterface(DataInterfaceClass);
}
