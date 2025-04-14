// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystemFunctionLibrary.h"

#include "Types/ItemData.h"

UItemDefinition* UItemSystemFunctionLibrary::GetItemDefinition(const FItemData& ItemData)
{
    FItemData* ItemDataPtr = const_cast<FItemData*>(&ItemData);
    return ItemDataPtr->GetItemDefinition();
}
