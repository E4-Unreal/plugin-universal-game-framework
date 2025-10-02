// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemInstanceFragment.h"

#include "Net/UnrealNetwork.h"

void UItemInstanceFragment::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Quantity);
}
