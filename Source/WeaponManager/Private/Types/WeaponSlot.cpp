// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/WeaponSlot.h"

#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"

const FWeaponSlot FWeaponSlot::EmptySlot { };

TScriptInterface<IWeaponInstanceInterface> FWeaponSlot::GetInstance() const
{
    if (Actor.IsValid() && Actor->Implements<UWeaponActorInterface>())
    {
        return IWeaponActorInterface::Execute_GetWeaponInstance(Actor.Get());
    }

    return nullptr;
}

TScriptInterface<IWeaponDataInterface> FWeaponSlot::GetData() const
{
    TScriptInterface<IWeaponInstanceInterface> Instance = GetInstance();

    return Instance ? IWeaponInstanceInterface::Execute_GetWeaponData(Instance.GetObject()) : nullptr;
}

const FName FWeaponSlot::GetActiveSocketName() const
{
    const TScriptInterface<IWeaponDataInterface>& Data = GetData();

    return Data ? IWeaponDataInterface::Execute_GetActiveSocketName(Data.GetObject()) : FName();
}

const FName FWeaponSlot::GetInActiveSocketName() const
{
    const TScriptInterface<IWeaponDataInterface>& Data = GetData();

    return Data ? IWeaponDataInterface::Execute_GetInActiveSocketName(Data.GetObject()) : FName();
}
