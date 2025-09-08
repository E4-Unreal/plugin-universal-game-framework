// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/WeaponSlot.h"

#include "Data/ReplicatedObject.h"
#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"

const FWeaponSlot FWeaponSlot::EmptySlot { };

UReplicatedObject* FWeaponSlot::GetInstance() const
{
    /*if (Actor.IsValid() && Actor->Implements<UWeaponActorInterface>())
    {
        return IWeaponActorInterface::Execute_GetInstance(Actor.Get());
    }*/

    return nullptr;
}

TSoftObjectPtr<UDataAsset> FWeaponSlot::GetData() const
{
    UReplicatedObject* Instance = GetInstance();

    return Instance && Instance->Implements<UWeaponInstanceInterface>() ? IWeaponInstanceInterface::Execute_GetData(Instance) : nullptr;
}

const FName FWeaponSlot::GetActiveSocketName() const
{
    TSoftObjectPtr<UDataAsset> Data = GetData();

    return !Data.IsNull() && Data->Implements<UWeaponDataInterface>() ? IWeaponDataInterface::Execute_GetActiveSocketName(Data.LoadSynchronous()) : FName();
}

const FName FWeaponSlot::GetInActiveSocketName() const
{
    TSoftObjectPtr<UDataAsset> Data = GetData();

    return !Data.IsNull() && Data->Implements<UWeaponDataInterface>() ? IWeaponDataInterface::Execute_GetInActiveSocketName(Data.LoadSynchronous()) : FName();
}
