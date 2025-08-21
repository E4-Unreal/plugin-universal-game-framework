// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuickSlotManagerComponent.h"

#include "Components/SocketManagerComponent.h"


UQuickSlotManagerComponent::UQuickSlotManagerComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    SlotNum = 4;
}

void UQuickSlotManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
    FindSocketManager();
}

void UQuickSlotManagerComponent::SetSlotIndex(int32 NewSlotIndex)
{
    if (NewSlotIndex == SlotIndex || NewSlotIndex < 0 || NewSlotIndex >= SlotNum) return;

    int32 OldSlotIndex = SlotIndex;
    SlotIndex = NewSlotIndex;
    OnSlotIndexChanged(OldSlotIndex);
}

void UQuickSlotManagerComponent::SetSlot(int32 InSlotIndex, FQuickSlot NewSlot)
{
    FQuickSlot& Slot = const_cast<FQuickSlot&>(GetSlot(InSlotIndex));
    if (Slot == NewSlot) return;

    if (Slot.IsValid())
    {
        SocketManager->DetachActorFromSocket(Slot.SocketTag);
        Slot.Actor->Destroy();
    }

    Slot = NewSlot;

    if (Slot.IsValid())
    {
        // TODO SpawnActor
        SocketManager->AttachActorToSocket(Slot.SocketTag, Slot.Actor);
    }
}

void UQuickSlotManagerComponent::CreateSlots()
{
    Slots.Reserve(SlotNum);

    for (int32 Index = 0; Index < SlotNum; ++Index)
    {
        Slots.Emplace(FQuickSlot());
    }
}

void UQuickSlotManagerComponent::FindSocketManager()
{
    if (SocketManager.IsValid()) return;

    SocketManager = GetOwner()->FindComponentByClass<USocketManagerComponent>();
}

void UQuickSlotManagerComponent::OnSlotIndexChanged(int32 OldSlotIndex)
{
    const FQuickSlot& OldSlot = GetSlot(OldSlotIndex);
    if (OldSlot.IsValid())
    {
        OldSlot.Actor->SetActorHiddenInGame(true);
        OldSlot.Actor->SetActorEnableCollision(false);
    }

    const FQuickSlot& NewSlot = GetCurrentSlot();
    if (NewSlot.IsValid())
    {
        NewSlot.Actor->SetActorHiddenInGame(false);
        NewSlot.Actor->SetActorEnableCollision(true);
    }
}
