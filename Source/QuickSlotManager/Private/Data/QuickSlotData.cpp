// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/QuickSlotData.h"

#include "GameplayTags/SocketGameplayTags.h"

UQuickSlotData::UQuickSlotData(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SocketTag = Socket::Character::RightHand;
}
