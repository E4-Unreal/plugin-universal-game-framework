// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/ItemContainer.h"

#include "Subsystems/ItemSubsystem.h"

UItemDefinition* FItemContainer::GetItemDefinition()
{
    if (ItemDefinition != nullptr) return ItemDefinition;

    ItemDefinition = GEngine->GetEngineSubsystem<UItemSubsystem>()->GetItemDefinitionByID(ID);

    return ItemDefinition;
}
