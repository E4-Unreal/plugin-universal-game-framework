// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstanceBase.h"

#include "Data/DataDefinitionBase.h"

void UDataInstanceBase::SetDefinition_Implementation(UDataDefinitionBase* NewDefinition)
{
    Definition = NewDefinition && DefinitionInterfaceClass && NewDefinition->GetClass()->ImplementsInterface(DefinitionInterfaceClass) ? NewDefinition : nullptr;
}
