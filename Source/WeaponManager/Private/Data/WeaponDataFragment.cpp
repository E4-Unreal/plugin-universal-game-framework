// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponDataFragment.h"

#include "GameplayTags/WeaponGameplayTags.h"
#include "Actors/WeaponActor.h"

UWeaponDataFragment::UWeaponDataFragment()
{
    SlotType = Weapon::Slot::Primary;
    ActorClass = AWeaponActor::StaticClass();
    ActiveSocketName = FName("hand_r");
    MaxDurability = 100;
}
