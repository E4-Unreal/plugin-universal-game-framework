// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponDataFragment.h"

#include "GameplayTags/WeaponGameplayTags.h"
#include "Actors/WeaponActor.h"
#include "Data/WeaponInstanceFragment.h"

UWeaponDataFragment::UWeaponDataFragment()
{
    SlotType = Weapon::Slot::Primary;
    ActorClass = AWeaponActor::StaticClass();
    ActiveSocketName = FName("hand_r");
    MaxDurability = 100;
}

UDataInstanceFragment* UWeaponDataFragment::CreateDataInstanceFragment() const
{
    auto WeaponInstanceFragment = NewObject<UWeaponInstanceFragment>();
    WeaponInstanceFragment->Durability = MaxDurability;

    return WeaponInstanceFragment;
}
