// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystemFunctionLibrary.h"

#include "Data/ItemConfig.h"
#include "Data/ItemDefinition.h"

const UItemConfig* UItemSystemFunctionLibrary::FindItemConfigByClass(UItemDefinition* ItemDefinition,
                                                                     TSubclassOf<UItemConfig> ItemConfigClass)
{
    if (ItemDefinition != nullptr && ItemConfigClass != nullptr)
    {
        return ItemDefinition->GetItemConfigByClass(ItemConfigClass);
    }
    return nullptr;
}
