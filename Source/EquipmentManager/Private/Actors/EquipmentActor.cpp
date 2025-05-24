// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EquipmentActor.h"
#include "Logging.h"

AEquipmentActor::AEquipmentActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AEquipmentActor::Equip_Implementation(AActor* NewOwner)
{
    LOG(Log, TEXT("%s equip %s"), *NewOwner->GetName(), *GetName())
    SetOwner(NewOwner);
}

void AEquipmentActor::UnEquip_Implementation()
{
    LOG(Log, TEXT("%s unequip %s"), *Owner->GetName(), *GetName())
    SetOwner(nullptr);
}
