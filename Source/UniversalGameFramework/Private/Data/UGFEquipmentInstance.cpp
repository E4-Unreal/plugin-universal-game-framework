// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFEquipmentInstance.h"

#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/WeaponManagerFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

void UUGFEquipmentInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Actor)
    DOREPLIFETIME(ThisClass, Durability)
}

void UUGFEquipmentInstance::SetDefinition_Implementation(UDataDefinitionBase* NewDefinition)
{
    Definition = NewDefinition;

    if (Definition)
    {
        const float MaxDurability = UWeaponManagerFunctionLibrary::GetMaxDurability(Definition);
        Durability = MaxDurability;
    }
}

void UUGFEquipmentInstance::SetDurability_Implementation(float NewDurability)
{
    if (Definition)
    {
        const float MaxDurability = UWeaponManagerFunctionLibrary::GetMaxDurability(Definition);
        Durability = FMath::Clamp(NewDurability, 0, MaxDurability);
    }
}
