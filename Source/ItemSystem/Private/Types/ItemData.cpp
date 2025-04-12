// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/ItemData.h"

#include "Subsystems/ItemSubsystem.h"

UItemDefinition* FItemData::GetItemDefinition()
{
    if (ItemDefinition != nullptr) return ItemDefinition;

    ItemDefinition = GEngine->GetWorld()->GetGameInstance()->GetSubsystem<UItemSubsystem>()->GetItemDefinitionByID(ID);

    return ItemDefinition;
}
