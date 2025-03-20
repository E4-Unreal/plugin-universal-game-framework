// Fill out your copyright notice in the Description page of Project Settings.


#include "UGFItemSystemFunctionLibrary.h"

#include "Logging.h"
#include "Data/UGFItemConfig.h"
#include "Data/UGFItemDefinition.h"

const UUGFItemConfig* UUGFItemSystemFunctionLibrary::FindItemConfigByClass(UUGFItemDefinition* ItemDefinition, TSubclassOf<UUGFItemConfig> ItemConfigClass)
{
    if ((ItemDefinition != nullptr) && (ItemConfigClass != nullptr))
    {
        return ItemDefinition->FindItemConfigByClass(ItemConfigClass);
    }
    return nullptr;
}

bool UUGFItemSystemFunctionLibrary::IsValidItem(const FUGFItem& Item)
{
    // null 검사
    if (Item.ItemDefinition == nullptr)
    {
        LOG(Error, TEXT("Item Definition is null"))
        return false;
    }

    // 입력 유효성 검사
    if (Item.Amount <= 0)
    {
        LOG(Error, TEXT("Item Amount: %d"), Item.Amount);
        return false;
    }

    return true;
}
