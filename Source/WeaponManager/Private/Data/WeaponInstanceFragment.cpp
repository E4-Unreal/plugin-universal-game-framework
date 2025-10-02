// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponInstanceFragment.h"

#include "Net/UnrealNetwork.h"

void UWeaponInstanceFragment::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Actor);
    DOREPLIFETIME(ThisClass, Durability);
}
