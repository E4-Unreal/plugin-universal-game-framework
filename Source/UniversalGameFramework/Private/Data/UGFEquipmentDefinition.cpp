// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFEquipmentDefinition.h"

#include "GameplayTags/InventoryGameplayTags.h"
#include "GameplayTags/WeaponGameplayTags.h"
#include "Actors/WeaponActor.h"
#include "Data/UGFEquipmentInstance.h"

UUGFEquipmentDefinition::UUGFEquipmentDefinition()
{
    DataInstanceClass = UUGFEquipmentInstance::StaticClass();

    MaxStack = 1;
    ItemType = Item::Equipment::Root;

    SlotType = Weapon::Slot::Primary;
    ActorClass = AWeaponActor::StaticClass();
    ActiveSocketName = FName("hand_r");
    MaxDurability = 100;
}
