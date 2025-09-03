// Fill out your copyright notice in the Description page of Project Settings.


#include "Types/WeaponSlot.h"

#include "Interfaces/WeaponDataInterface.h"

const FWeaponSlot FWeaponSlot::EmptySlot { };

const FName FWeaponSlot::GetActiveSocketName() const
{
    return Data ? IWeaponDataInterface::Execute_GetActiveSocketName(Data.GetObject()) : FName();
}

const FName FWeaponSlot::GetInActiveSocketName() const
{
    return Data ? IWeaponDataInterface::Execute_GetInActiveSocketName(Data.GetObject()) : FName();
}
