// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/WeaponSlot.h"

#include "Interfaces/WeaponDataInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"

const FWeaponSlot FWeaponSlot::EmptySlot { };

TScriptInterface<IWeaponDataInterface> FWeaponSlot::GetData() const
{
    return WeaponInstance ? IWeaponInstanceInterface::Execute_GetData(WeaponInstance.GetObject()) : nullptr;
}

void FWeaponSlot::SetData(const TScriptInterface<IWeaponDataInterface>& NewData)
{
    if (WeaponInstance)
    {
        IWeaponInstanceInterface::Execute_SetData(WeaponInstance.GetObject(), NewData);
    }
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

AActor* FWeaponSlot::GetActor() const
{
    return WeaponInstance ? IWeaponInstanceInterface::Execute_GetActor(WeaponInstance.GetObject()) : nullptr;
}

void FWeaponSlot::SetActor(AActor* NewActor)
{
    if (WeaponInstance)
    {
        IWeaponInstanceInterface::Execute_SetActor(WeaponInstance.GetObject(), NewActor);
    }
}
