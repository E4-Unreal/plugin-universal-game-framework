// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DefinitionContainerBase.h"

#include "Net/UnrealNetwork.h"

void UDefinitionContainerBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Definition);
}

void UDefinitionContainerBase::SetDefinition_Implementation(UDataDefinitionBase* NewDefinition)
{
    Definition = NewDefinition;
}
