// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFEquipmentDefinition.h"

#include "GameplayTags/WeaponGameplayTags.h"
#include "Actors/WeaponActor.h"
#include "Data/WeaponInstance.h"

UUGFEquipmentDefinition::UUGFEquipmentDefinition()
{
    InstanceClass = UWeaponInstance::StaticClass();

    SlotType = Weapon::Slot::Primary;
    ActorClass = AWeaponActor::StaticClass();
    ActiveSocketName = FName("hand_r");
    MaxDurability = 100;
}
