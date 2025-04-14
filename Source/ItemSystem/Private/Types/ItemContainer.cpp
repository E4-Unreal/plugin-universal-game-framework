// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/ItemContainer.h"

#include "Subsystems/ItemSubsystem.h"

UItemDefinition* FItemContainer::GetItemDefinition()
{
    if (ItemDefinition != nullptr) return ItemDefinition;

    if (GEngine)
    {
        if (auto ItemSubsystem = GEngine->GetEngineSubsystem<UItemSubsystem>())
        {
            return ItemSubsystem->GetItemDefinitionByID(ID);
        }
    }

    return nullptr;
}
