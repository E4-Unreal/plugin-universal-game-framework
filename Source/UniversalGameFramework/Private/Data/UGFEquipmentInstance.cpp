// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFEquipmentInstance.h"

#include "FunctionLibraries/WeaponDataFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

void UUGFEquipmentInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Actor)
    DOREPLIFETIME(ThisClass, Durability)
}

void UUGFEquipmentInstance::SetDefinition(UDataDefinitionBase* NewDefinition)
{
    Super::SetDefinition(NewDefinition);

    if (UWeaponDataFunctionLibrary::HasWeaponData(Definition))
    {
        const float MaxDurability = UWeaponDataFunctionLibrary::GetMaxDurability(Definition);
        Durability = MaxDurability;
    }
}

void UUGFEquipmentInstance::SetDurability_Implementation(float NewDurability)
{
    if (UWeaponDataFunctionLibrary::HasWeaponData(Definition))
    {
        const float MaxDurability = UWeaponDataFunctionLibrary::GetMaxDurability(Definition);
        Durability = FMath::Clamp(NewDurability, 0, MaxDurability);
    }
}
