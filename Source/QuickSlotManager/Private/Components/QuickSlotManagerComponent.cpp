// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuickSlotManagerComponent.h"

#include "Components/SocketManagerComponent.h"
#include "Interfaces/QuickSlotActorInterface.h"


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

/*void UQuickSlotManagerComponent::SwapSlots_Implementation(int32 SourceIndex, int32 DestinationIndex)
{
    const FQuickSlot& SourceSlot = GetSlot(SourceIndex);
    const FQuickSlot& DestinationSlot = GetSlot(DestinationIndex);

    FQuickSlot OldSourceSlot = SourceSlot;
    FQuickSlot OldDestinationSlot = DestinationSlot;

    const_cast<FQuickSlot&>(SourceSlot) = OldDestinationSlot;
    const_cast<FQuickSlot&>(DestinationSlot) = OldSourceSlot;

    SlotUpdatedDelegate.Broadcast(SourceIndex);
    SlotUpdatedDelegate.Broadcast(DestinationIndex);
}*/

void UQuickSlotManagerComponent::SetSlotIndex(int32 NewSlotIndex)
{
    if (NewSlotIndex == SlotIndex || NewSlotIndex < 0 || NewSlotIndex >= SlotNum) return;

    int32 OldSlotIndex = SlotIndex;
    SlotIndex = NewSlotIndex;
    OnSlotIndexChanged(OldSlotIndex);
}

void UQuickSlotManagerComponent::SetSlotByData(int32 InSlotIndex,
    const TScriptInterface<IQuickSlotDataInterface>& NewData)
{
    FQuickSlot& Slot = const_cast<FQuickSlot&>(GetSlot(InSlotIndex));
    if (Slot.Data == NewData) return;

    if (!Slot.IsEmpty())
    {
        //SocketManager->DestroyActorFromSocket(Slot.GetSocketTag());
        Slot = FQuickSlot::EmptySlot;
    }

    Slot.Data = NewData;

    if (!Slot.IsEmpty())
    {
        /*if (AActor* SpawnedActor = SocketManager->SpawnActorToSocket(Slot.GetSocketTag(), Slot.GetActorClass()))
        {
            Slot.Actor = SpawnedActor;
            if (Slot.Actor->Implements<UQuickSlotActorInterface>())
            {
                IQuickSlotActorInterface::Execute_SetQuickSlotData(SpawnedActor, Slot.Data);
            }

            if (InSlotIndex != SlotIndex)
            {
                SpawnedActor->SetActorHiddenInGame(false);
                SpawnedActor->SetActorEnableCollision(true);
            }
        }*/
    }

    /*SlotUpdatedDelegate.Broadcast(InSlotIndex);*/
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
    if (!OldSlot.IsEmpty() && OldSlot.Actor)
    {
        OldSlot.Actor->SetActorHiddenInGame(true);
        OldSlot.Actor->SetActorEnableCollision(false);
    }

    const FQuickSlot& NewSlot = GetCurrentSlot();
    if (!OldSlot.IsEmpty() && NewSlot.Actor)
    {
        NewSlot.Actor->SetActorHiddenInGame(false);
        NewSlot.Actor->SetActorEnableCollision(true);
    }

    /*SlotIndexChangedDelegate.Broadcast(OldSlotIndex, SlotIndex);*/
}
