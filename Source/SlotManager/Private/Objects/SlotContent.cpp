// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/SlotContent.h"

#include "Net/UnrealNetwork.h"

void USlotContent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Data);
}
