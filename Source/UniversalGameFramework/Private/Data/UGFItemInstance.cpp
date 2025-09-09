// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemInstance.h"

#include "Net/UnrealNetwork.h"

void UUGFItemInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Quantity)
}
