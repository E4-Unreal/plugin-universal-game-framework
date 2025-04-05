// Fill out your copyright notice in the Description page of Project Settings.


#include "UGFItemSystemFunctionLibrary.h"

#include "Logging.h"
#include "Data/UGFItemConfig.h"
#include "Data/UGFItemDefinition.h"

const UUGFItemConfig* UUGFItemSystemFunctionLibrary::FindItemConfigByClass(UUGFItemDefinition* ItemDefinition, TSubclassOf<UUGFItemConfig> ItemConfigClass)
{
    if ((ItemDefinition != nullptr) && (ItemConfigClass != nullptr))
    {
        return ItemDefinition->GetItemConfigByClass(ItemConfigClass);
    }
    return nullptr;
}
