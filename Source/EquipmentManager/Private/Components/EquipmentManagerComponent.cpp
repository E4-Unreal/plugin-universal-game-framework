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

bool UEquipmentManagerComponent::HasSlot(const FGameplayTag& EquipmentType, const int32 Index) const
{
    if (bool bValidInput = EquipmentType.IsValid() && Index >= 0; !bValidInput) return false;

    for (const auto& Slot : Slots)
    {
        if (EquipmentType == Slot.EquipmentType && Slot.Index == Index)
        {
            return true;
        }
    }

    return false;
}

const FEquipmentSlot& UEquipmentManagerComponent::GetSlot(const FGameplayTag& EquipmentType, const int32 Index) const
{
    for (const auto& Slot : Slots)
    {
        if (Slot.EquipmentType == EquipmentType && Slot.Index == Index)
        {
            return Slot;
        }
    }

    return FEquipmentSlot::EmptySlot;
}

bool UEquipmentManagerComponent::AddEquipmentToSlot(const TScriptInterface<IEquipmentInterface>& NewEquipment,
    const FGameplayTag& EquipmentType, int32 Index)
{
    if (!NewEquipment) return false;
    if (!HasSlot(EquipmentType, Index)) return false;

    FEquipmentSlot& Slot = GetSlotRef(EquipmentType, Index);
    if (Slot.IsValid() && Slot.IsEmpty())
    {
        Slot.Equipment = NewEquipment;
        Slot.Equipment->Equip(GetOwner());
        AttachActorToSocket(Slot.Socket, CastChecked<AActor>(NewEquipment.GetObject()));

        return true;
    }

    return false;
}

TScriptInterface<IEquipmentInterface> UEquipmentManagerComponent::RemoveEquipmentFromSlot(
    const FGameplayTag& EquipmentType, int32 Index)
{
    if (!HasSlot(EquipmentType, Index)) return nullptr;

    FEquipmentSlot& Slot = GetSlotRef(EquipmentType, Index);
    if (Slot.IsValid() && !Slot.IsEmpty())
    {
        AActor* OldEquipmentActor = DetachActorFromSocket(Slot.Socket);
        Slot.Equipment->UnEquip();
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
            NewEquipmentSlot.EquipmentType = EquipmentType;
            NewEquipmentSlot.Index = Index;

            Slots.Emplace(NewEquipmentSlot);
        }
    }
}
