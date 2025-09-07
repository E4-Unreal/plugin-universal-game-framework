// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemInstance.h"

#include "Interfaces/WeaponDataInterface.h"
#include "Net/UnrealNetwork.h"

void UUGFItemInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Quantity)
    DOREPLIFETIME(ThisClass, Actor)
    DOREPLIFETIME(ThisClass, Durability)
}

void UUGFItemInstance::SetData_Implementation(UDataAsset* NewData)
{
    Super::SetData_Implementation(NewData);

    if (Data)
    {
        if (Data->Implements<UWeaponDataInterface>())
        {
            const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Data);
            Durability = MaxDurability;
        }
    }
}

void UUGFItemInstance::SetDurability_Implementation(float NewDurability)
{
    if (Data)
    {
        if (Data->Implements<UWeaponDataInterface>())
        {
            const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Data);
            Durability = FMath::Clamp(NewDurability, 0, MaxDurability);
        }
    }
}
