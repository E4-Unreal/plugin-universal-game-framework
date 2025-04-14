// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystemFunctionLibrary.h"

#include "Data/ItemConfig.h"
#include "Data/ItemDefinition.h"
#include "Types/ItemData.h"

const UItemConfig* UItemSystemFunctionLibrary::FindItemConfigByClass(UItemDefinition* ItemDefinition,
                                                                     TSubclassOf<UItemConfig> ItemConfigClass)
{
    if (ItemDefinition == nullptr || ItemConfigClass == nullptr) return nullptr;

    return nullptr;
}

UItemDefinition* UItemSystemFunctionLibrary::GetItemDefinition(const FItemData& ItemData)
{
    FItemData* ItemDataPtr = const_cast<FItemData*>(&ItemData);
    return ItemDataPtr->GetItemDefinition();
}
