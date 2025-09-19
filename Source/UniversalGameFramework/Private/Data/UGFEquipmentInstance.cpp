// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFEquipmentInstance.h"

#include "Interfaces/WeaponDataInterface.h"
#include "Net/UnrealNetwork.h"

void UUGFEquipmentInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Actor)
    DOREPLIFETIME(ThisClass, Durability)
}

void UUGFEquipmentInstance::SetData_Implementation(UDataAsset* NewData)
{
    Data = NewData;

    if (Data && Data->Implements<UWeaponDataInterface>())
    {
        const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Data);
        Durability = MaxDurability;
    }
}

void UUGFEquipmentInstance::SetDurability_Implementation(float NewDurability)
{
    if (Data && Data->Implements<UWeaponDataInterface>())
    {
        const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Data);
        Durability = FMath::Clamp(NewDurability, 0, MaxDurability);
    }
}
