// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDatabase.h"

#include "Logging.h"
#include "Data/ItemDefinition.h"

UItemDefinition* UItemDatabase::GetItemDefinitionByID(int32 ID)
{
    if (ID < 0 || !ItemDefinitionMap.Contains(ID))
    {
        LOG(Error, TEXT("ItemDefinition(ID: %d) is not exist!"), ID)
        return nullptr;
    }

    return ItemDefinitionMap[ID];
}
