// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataFragment.h"

#include "Data/ItemInstanceFragment.h"
#include "GameplayTags/InventoryGameplayTags.h"

UItemDataFragment::UItemDataFragment()
{
    MaxStack = 1;
    ItemType = Item::Root;
}

UDataInstanceFragment* UItemDataFragment::CreateDataInstanceFragment() const
{
    auto ItemInstanceFragment = NewObject<UItemInstanceFragment>();

    return ItemInstanceFragment;
}
