// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponDefinition.h"

#include "Actors/WeaponActor.h"
#include "GameplayTags/WeaponGameplayTags.h"

UWeaponDefinition::UWeaponDefinition()
{
    ActorClass = AWeaponActor::StaticClass();
    SlotType = Weapon::Slot::Primary;
    ActiveSocketName = FName("hand_r");
}
