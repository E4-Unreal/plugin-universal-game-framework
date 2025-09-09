// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinition.h"

#include "Data/UGFItemInstance.h"
#include "GameplayTags/CurrencyGameplayTags.h"
#include "GameplayTags/InventoryGameplayTags.h"

UUGFItemDefinition::UUGFItemDefinition()
{
    InstanceClass = UUGFItemInstance::StaticClass();

    MaxStack = 10;
    ItemType = Item::Root;

    CurrencyType = Currency::Default;
}
