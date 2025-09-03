// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/ItemInstance.h"

int32 FItemInstance::GetMaxStack() const
{
    return IsValid() ? IItemDataInterface::Execute_GetMaxStack(Data.GetObject()) : 0;
}

int32 FItemInstance::GetCapacity() const
{
    return IsValid() ? GetMaxStack() - Quantity : 0;
}

FGameplayTag FItemInstance::GetItemType() const
{
    return IsValid() ? IItemDataInterface::Execute_GetItemType(Data.GetObject()) : FGameplayTag::EmptyTag;
}
