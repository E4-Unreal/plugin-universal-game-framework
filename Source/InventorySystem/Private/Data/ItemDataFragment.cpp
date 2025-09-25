// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDataFragment.h"

#include "GameplayTags/InventoryGameplayTags.h"

UItemDataFragment::UItemDataFragment()
{
    MaxStack = 1;
    ItemType = Item::Root;
}
