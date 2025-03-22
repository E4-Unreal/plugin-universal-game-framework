// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFInventoryItemConfig.h"

#include "Data/UGFItemDefinition.h"

const UUGFInventoryItemConfig* UUGFInventoryItemConfig::GetFromItemDefinition(const UUGFItemDefinition* ItemDefinition)
{
    return ItemDefinition == nullptr ? nullptr : ItemDefinition->GetItemConfigByClass(TSubclassOf<UUGFInventoryItemConfig>(StaticClass()));
}
