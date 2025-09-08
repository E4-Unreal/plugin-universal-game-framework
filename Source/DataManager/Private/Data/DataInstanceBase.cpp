// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstanceBase.h"

#include "Data/DataDefinitionBase.h"

void UDataInstanceBase::SetDefinition_Implementation(UDataDefinitionBase* NewDefinition)
{
    Definition = NewDefinition && CanCreateFromData(NewDefinition->GetClass()) ? NewDefinition : nullptr;
}

bool UDataInstanceBase::CanCreateFromData(TSubclassOf<UDataDefinitionBase> DefinitionClass)
{
    return DefinitionClass && DefinitionInterfaceClass && DefinitionClass->ImplementsInterface(DefinitionInterfaceClass);
}
