// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataContainerBase.h"

#include "Net/UnrealNetwork.h"

void UDataContainerBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Data);
}

bool UDataContainerBase::IsValid_Implementation() const
{
    return Data != nullptr;
}

UDataAsset* UDataContainerBase::GetData_Implementation() const
{
    return Data;
}

void UDataContainerBase::SetData_Implementation(UDataAsset* NewData)
{
    Data = NewData;
}
