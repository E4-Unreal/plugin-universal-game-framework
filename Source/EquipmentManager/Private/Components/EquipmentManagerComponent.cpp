// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentManagerComponent.h"

#include "Interfaces/EquipmentInterface.h"


UEquipmentManagerComponent::UEquipmentManagerComponent()
{
    bWantsInitializeComponent = true;
}

void UEquipmentManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
}

bool UEquipmentManagerComponent::HasSlot(const FEquipmentSlotIndex& SlotIndex) const
{
    if (!SlotIndex.IsValid()) return false;

    for (const auto& Slot : Slots)
    {
        if (Slot.SlotIndex == SlotIndex)
        {
            return true;
        }
    }

    return false;
}

const FEquipmentSlot& UEquipmentManagerComponent::GetSlot(const FEquipmentSlotIndex& SlotIndex) const
{
    for (const auto& Slot : Slots)
    {
        if (Slot.SlotIndex == SlotIndex)
        {
            return Slot;
        }
    }

    return FEquipmentSlot::EmptySlot;
}

bool UEquipmentManagerComponent::AddEquipmentToSlot(const TScriptInterface<IEquipmentInterface>& NewEquipment, const FEquipmentSlotIndex& SlotIndex)
{
    if (!NewEquipment) return false;
    if (!HasSlot(SlotIndex)) return false;

    FEquipmentSlot& Slot = GetSlotRef(SlotIndex);
    if (Slot.IsValid() && Slot.IsEmpty())
    {
        Slot.Equipment = NewEquipment;
        IEquipmentInterface::Execute_Equip(Slot.Equipment.GetObject(), GetOwner());
        AttachActorToSocket(Slot.Socket, CastChecked<AActor>(NewEquipment.GetObject()));

        return true;
    }

    return false;
}

TScriptInterface<IEquipmentInterface> UEquipmentManagerComponent::RemoveEquipmentFromSlot(const FEquipmentSlotIndex& SlotIndex)
{
    if (!HasSlot(SlotIndex)) return nullptr;

    FEquipmentSlot& Slot = GetSlotRef(SlotIndex);
    if (Slot.IsValid() && !Slot.IsEmpty())
    {
        AActor* OldEquipmentActor = DetachActorFromSocket(Slot.Socket);
        IEquipmentInterface::Execute_UnEquip(Slot.Equipment.GetObject());
        Slot.Equipment = nullptr;

        return OldEquipmentActor;
    }

    return nullptr;
}

void UEquipmentManagerComponent::CreateSlots()
{
    Slots.Reset(SlotConfigs.Num());

    for (const auto& [EquipmentType, Sockets] : SlotConfigs)
    {
        for (int32 Index = 0; Index < Sockets.Num(); ++Index)
        {
            FEquipmentSlot NewEquipmentSlot;
            NewEquipmentSlot.SlotIndex = FEquipmentSlotIndex(EquipmentType, Index);
            NewEquipmentSlot.Socket = Sockets[Index];

            Slots.Emplace(NewEquipmentSlot);
        }
    }
}
