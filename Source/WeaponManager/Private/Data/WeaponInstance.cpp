// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponInstance.h"

#include "Data/DataDefinitionBase.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Net/UnrealNetwork.h"

void UWeaponInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Actor);
    DOREPLIFETIME(ThisClass, Durability);
}

void UWeaponInstance::SetDefinition_Implementation(UDataDefinitionBase* NewDefinition)
{
    Definition = NewDefinition;

    if (Definition)
    {
        const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Definition);
        Durability = MaxDurability;
    }
}

void UWeaponInstance::SetDurability_Implementation(float NewDurability)
{
    if (Definition)
    {
        const float MaxDurability = IWeaponDataInterface::Execute_GetMaxDurability(Definition);
        Durability = FMath::Clamp(NewDurability, 0, MaxDurability);
    }
}
