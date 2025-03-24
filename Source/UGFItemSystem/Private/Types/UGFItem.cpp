// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/UGFItem.h"

#include "Logging.h"

bool FUGFItem::IsValid() const
{
    // ItemDefinition 유효성 검사
    if (ItemDefinition == nullptr)
    {
        LOG_NULL(ItemDefinition)
        return false;
    }

    // Quantity 유효성 검사
    if (Quantity <= 0)
    {
        LOG(Error, TEXT("Item Amount: %d"), Quantity);
        return false;
    }

    return true;
}
