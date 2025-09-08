// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstance.h"

#include "Net/UnrealNetwork.h"

void UDataInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Data);
}

UDataAsset* UDataInstance::GetData_Implementation() const
{
    return Data;
}

void UDataInstance::SetData_Implementation(UDataAsset* NewData)
{
    Data = NewData;
}
