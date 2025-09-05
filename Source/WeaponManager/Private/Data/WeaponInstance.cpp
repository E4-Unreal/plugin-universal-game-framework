// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponInstance.h"

#include "Interfaces/WeaponDataInterface.h"
#include "Net/UnrealNetwork.h"

void UWeaponInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Data);
    DOREPLIFETIME(ThisClass, Durability);
}

void UWeaponInstance::SetDurability_Implementation(float NewDurability)
{
    if (Data)
    {
        const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Data.GetObject());
        Durability = FMath::Clamp(NewDurability, 0, MaxDurability);
    }
}
