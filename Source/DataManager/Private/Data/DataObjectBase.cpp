// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataObjectBase.h"

#include "Net/UnrealNetwork.h"

void UDataObjectBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Data);
}
