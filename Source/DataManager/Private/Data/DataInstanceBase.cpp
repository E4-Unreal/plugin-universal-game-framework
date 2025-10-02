// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstanceBase.h"

#include "Net/UnrealNetwork.h"

void UDataInstanceBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Definition);
}

UObject* UDataInstanceBase::GetDataInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    return InterfaceClass && GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<ThisClass*>(this) : nullptr;
}
