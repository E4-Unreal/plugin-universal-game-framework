// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SlotManagerComponentBase.h"

#include "Net/UnrealNetwork.h"

USlotManagerComponentBase::USlotManagerComponentBase()
{
    bWantsInitializeComponent = true;
}

void USlotManagerComponentBase::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
    MappingSlots();
}

void USlotManagerComponentBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Slots);
}

bool USlotManagerComponentBase::DoesSlotExist(int32 Index) const
{
    return SlotMap.Contains(Index);
}

bool USlotManagerComponentBase::IsEmpty(int32 Index) const
{
    return DoesSlotExist(Index) ? GetContent(Index) == nullptr : false;
}

UReplicatedObject* USlotManagerComponentBase::GetContent(int32 Index) const
{
    return SlotMap.FindRef(Index);
}

int32 USlotManagerComponentBase::GetEmptySlotIndex() const
{
    int32 EmptyIndex = -1;

    for (int32 Index = 0; Index < Slots.Num(); ++Index)
    {
        if (IsEmpty(Index))
        {
            EmptyIndex = Index;

            break;
        }
    }

    return EmptyIndex;
}

void USlotManagerComponentBase::SetContent(int32 Index, UReplicatedObject* NewContent)
{
    if (DoesSlotExist(Index))
    {
        Slots[Index].Content = NewContent;
        SlotMap.Emplace(Index, NewContent);

        OnSlotUpdated.Broadcast(Index);
    }
}

void USlotManagerComponentBase::AddContent(UReplicatedObject* NewContent)
{
    SetContent(GetEmptySlotIndex(), NewContent);
}

void USlotManagerComponentBase::TransferContent(USlotManagerComponentBase* Source, int32 SourceIndex,
                                                USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    if (Source && !Source->IsEmpty(SourceIndex) && Destination && Destination->IsEmpty(DestinationIndex))
    {
        UReplicatedObject* Content = Source->GetContent(DestinationIndex);
        Source->SetContent(SourceIndex, nullptr);
        Destination->SetContent(DestinationIndex, Content);
    }
}

void USlotManagerComponentBase::SwapContent(USlotManagerComponentBase* Source, int32 SourceIndex,
    USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    if (Source && Destination)
    {
        if (!Source->IsEmpty(SourceIndex) && Destination->IsEmpty(DestinationIndex))
        {
            TransferContent(Source, SourceIndex, Destination, DestinationIndex);
        }
        else if (Source->IsEmpty(SourceIndex) && !Destination->IsEmpty(DestinationIndex))
        {
            TransferContent(Destination, DestinationIndex, Source, SourceIndex);
        }
        else if (!Source->IsEmpty(SourceIndex) && !Destination->IsEmpty(DestinationIndex))
        {
            UReplicatedObject* SourceContent = Source->GetContent(DestinationIndex);
            UReplicatedObject* DestinationContent = Destination->GetContent(SourceIndex);
            Source->SetContent(SourceIndex, DestinationContent);
            Destination->SetContent(DestinationIndex, SourceContent);
        }
    }
}

void USlotManagerComponentBase::SyncContent(USlotManagerComponentBase* Source, int32 SourceIndex,
    USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    if (Source && !Source->IsEmpty(SourceIndex) && Destination && Destination->IsEmpty(DestinationIndex))
    {
        UReplicatedObject* Content = Source->GetContent(DestinationIndex);
        Destination->SetContent(DestinationIndex, Content);
    }
}

void USlotManagerComponentBase::CreateSlots()
{
    const int32 MaxSlotNum = GetMaxSlotNum();
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        Slots.Emplace(Index, nullptr);
    }
}

void USlotManagerComponentBase::MappingSlots()
{
    SlotMap.Empty(Slots.Num());
    for (const auto& [Index, Content] : Slots)
    {
        SlotMap.Emplace(Index, Content);
    }
}

void USlotManagerComponentBase::OnRep_Slots(TArray<FContentSlot> OldSlots)
{
    TArray<int32> UpdatedSlotIndices;

    for (const auto& [Index, Content] : Slots)
    {
        if (SlotMap.Contains(Index) && SlotMap[Index] == Content)
        {
            SlotMap.Remove(Index);
        }
        else
        {
            UpdatedSlotIndices.Emplace(Index);
        }
    }

    for (const auto& [Index, Content] : SlotMap)
    {
        UpdatedSlotIndices.Emplace(Index);
    }

    MappingSlots();

    for (int32 Index : UpdatedSlotIndices)
    {
        OnSlotUpdated.Broadcast(Index);
    }
}
