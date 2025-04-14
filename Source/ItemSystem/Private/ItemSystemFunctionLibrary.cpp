// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystemFunctionLibrary.h"

#include "Types/ItemContainer.h"

UItemDefinition* UItemSystemFunctionLibrary::GetItemDefinition(const FItemContainer& ItemData)
{
    return ItemData.GetItemDefinition();
}
