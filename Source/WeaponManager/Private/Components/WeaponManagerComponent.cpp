// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;
}

void UWeaponManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
}

void UWeaponManagerComponent::CreateSlots()
{
    if (!Slots.IsEmpty()) return;

    for (const auto& [SlotType, MaxNum] : SlotConfig)
    {
        for (int32 Index = 0; Index < MaxNum; ++Index)
        {
            Slots.Emplace(FWeaponSlot(SlotType, Index));
        }
    }
}
