// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ItemSubsystem.h"

#include "ItemSystemSettings.h"
#include "Data/ItemDatabase.h"

UItemDefinition* UItemSubsystem::GetItemDefinitionByID(int32 ID)
{
    auto ItemSystemSettings = GetMutableDefault<UItemSystemSettings>();
    auto ItemDatabase = ItemSystemSettings->GetItemDatabase();

    return ItemDatabase != nullptr ? ItemDatabase->GetItemDefinitionByID(ID) : nullptr;
}
