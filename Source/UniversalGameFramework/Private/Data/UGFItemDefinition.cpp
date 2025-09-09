// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinition.h"

#include "Data/ItemInstance.h"
#include "GameplayTags/CurrencyGameplayTags.h"

UUGFItemDefinition::UUGFItemDefinition()
{
    InstanceClass = UItemInstance::StaticClass();
    CurrencyType = Currency::Default;
}
