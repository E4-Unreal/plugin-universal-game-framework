// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentManagerComponent.h"

#include "Components/SocketManagerComponent.h"
#include "Interfaces/EquipmentActorInterface.h"
#include "Interfaces/EquipmentDataInterface.h"
#include "GameplayTags/EquipmentTypeTags.h"


UEquipmentManagerComponent::UEquipmentManagerComponent()
{
    bWantsInitializeComponent = true;
}

void UEquipmentManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
    FindSocketManager();
}

void UEquipmentManagerComponent::SelectWeapon(int32 Index)
{
    FGameplayTag WeaponTypeTag = Equipment::Weapon::Root;
    int32 WeaponSlotNum = GetSlotNum(WeaponTypeTag);
    if (Index < 0 || Index > WeaponSlotNum - 1) return;

    SelectedWeapon = GetSlot(WeaponTypeTag, Index).Equipment;
}

bool UEquipmentManagerComponent::HasSlot(FGameplayTag EquipmentType, int32 Index) const
{
    for (const auto& Slot : Slots)
    {
        if (Slot.EquipmentType == EquipmentType && Slot.Index == Index)
        {
            return true;
        }
    }

    return false;
}

const FEquipmentSlot& UEquipmentManagerComponent::GetSlot(FGameplayTag EquipmentType, int32 Index) const
{
    for (const FEquipmentSlot& Slot : Slots)
    {
        if (Slot.EquipmentType == EquipmentType && Slot.Index == Index)
        {
            return Slot;
        }
    }

    return FEquipmentSlot::EmptySlot;
}

bool UEquipmentManagerComponent::AddEquipmentToSlot(AActor* NewEquipment, FGameplayTag EquipmentType, int32 Index)
{
    if (!NewEquipment) return false;
    if (!HasSlot(EquipmentType, Index)) return false;

    FEquipmentSlot& Slot = GetSlotRef(EquipmentType, Index);
    if (Slot.IsValid() && Slot.IsEmpty())
    {
        Slot.Equipment = NewEquipment;
        IEquipmentActorInterface::Execute_Equip(Slot.Equipment, GetOwner());
        //SocketManager->AttachActorToSocket(Slot.Socket, NewEquipment);

        return true;
    }

    return false;
}

AActor* UEquipmentManagerComponent::RemoveEquipmentFromSlot(FGameplayTag EquipmentType, int32 Index)
{
    if (!HasSlot(EquipmentType, Index)) return nullptr;

    FEquipmentSlot& Slot = GetSlotRef(EquipmentType, Index);
    if (Slot.IsValid() && !Slot.IsEmpty())
    {
        //AActor* OldEquipmentActor = SocketManager->DetachActorFromSocket(Slot.Socket);
        IEquipmentActorInterface::Execute_UnEquip(Slot.Equipment);
        Slot.Equipment = nullptr;

        //return OldEquipmentActor;
    }

    return nullptr;
}

void UEquipmentManagerComponent::CreateSlots()
{
    Slots.Reset(SlotConfigs.Num());

    for (const auto& [EquipmentType, Sockets] : SlotConfigs)
    {
        if (SlotNumMap.Contains(EquipmentType)) continue;
        SlotNumMap.Emplace(EquipmentType, Sockets.Num());

        for (int32 Index = 0; Index < Sockets.Num(); ++Index)
        {
            FEquipmentSlot NewEquipmentSlot;
            NewEquipmentSlot.EquipmentType = EquipmentType;
            NewEquipmentSlot.Index = Index;
            NewEquipmentSlot.Socket = Sockets[Index];

            Slots.Emplace(NewEquipmentSlot);
        }
    }
}

void UEquipmentManagerComponent::FindSocketManager()
{
    if (SocketManager.IsValid()) return;

    SocketManager = GetOwner()->FindComponentByClass<USocketManagerComponent>();
}
