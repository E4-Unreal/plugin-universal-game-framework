// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDataTableRow.h"

#include "GameplayTags/CurrencyGameplayTags.h"
#include "GameplayTags/InventoryGameplayTags.h"
#include "GameplayTags/WeaponGameplayTags.h"

FUGFItemDataTableRow::FUGFItemDataTableRow()
{
    MaxStack = 1;
    ItemType = Item::Root;
    CurrencyType = Currency::Default;
    SlotType = Weapon::Slot::Primary;
    ActiveSocketName = "hand_r";
    MaxDurability = 100;
}
