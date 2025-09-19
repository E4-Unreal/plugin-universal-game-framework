// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SlotManagerComponentBase.h"

#include "Net/UnrealNetwork.h"
#include "Logging.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/DataInstanceInterface.h"
#include "Interfaces/DataInterface.h"

USlotManagerComponentBase::USlotManagerComponentBase()
{
    bWantsInitializeComponent = true;
}

void USlotManagerComponentBase::InitializeComponent()
{
    Super::InitializeComponent();

    OnSlotUpdated.AddDynamic(this, &ThisClass::HandleOnSlotUpdated);
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

bool USlotManagerComponentBase::IsSlotEmpty(int32 Index) const
{
    return DoesSlotExist(Index) ? GetContent(Index) == nullptr : false;
}

bool USlotManagerComponentBase::HasContent(UObject* InContent) const
{
    for (const auto& [Index, Content] : SlotMap)
    {
        if (Content == InContent)
        {
            return true;
        }
    }

    return false;
}

UObject* USlotManagerComponentBase::GetContent(int32 Index) const
{
    return SlotMap.FindRef(Index);
}

UDataAsset* USlotManagerComponentBase::GetData(int32 Index) const
{
    return GetDataFromContent(GetContent(Index));
}

int32 USlotManagerComponentBase::GetEmptySlotIndex(UObject* NewContent) const
{
    int32 EmptyIndex = -1;

    for (int32 Index = 0; Index < Slots.Num(); ++Index)
    {
        if (IsSlotEmpty(Index))
        {
            EmptyIndex = Index;

            break;
        }
    }

    return EmptyIndex;
}

void USlotManagerComponentBase::SetContent(int32 Index, UObject* NewContent)
{
    if (!GetOwner()->HasAuthority()) return;

    if (DoesSlotExist(Index))
    {
        UObject* OldContent = Slots[Index].Content;
        if (OldContent) RemoveReplicatedObject(Cast<UReplicatedObject>(OldContent));
        if (NewContent) AddReplicatedObject(Cast<UReplicatedObject>(NewContent));

        Slots[Index].Content = NewContent;
        SlotMap.Emplace(Index, NewContent);

        OnSlotUpdated.Broadcast(Index);
    }
}

bool USlotManagerComponentBase::AddContent(UObject* NewContent)
{
    if (!GetOwner()->HasAuthority()) return false;

    int32 EmptyIndex = GetEmptySlotIndex(NewContent);
    if (DoesSlotExist(EmptyIndex))
    {
        SetContent(EmptyIndex, NewContent);

        return true;
    }

    return false;
}

bool USlotManagerComponentBase::AddContentByData(UDataAsset* NewData)
{
    if (CheckData(NewData))
    {
        UObject* NewContent = IDataInterface::Execute_CreateDataInstance(NewData);
        return AddContent(NewContent);
    }

    return false;
}

bool USlotManagerComponentBase::RemoveContent(UObject* InContent)
{
    if (!GetOwner()->HasAuthority()) return false;

    for (const auto& [Index, Content] : SlotMap)
    {
        if (Content == InContent)
        {
            SetContent(Index, nullptr);

            return true;
        }
    }

    return false;
}

void USlotManagerComponentBase::TransferContent_Implementation(USlotManagerComponentBase* Source, int32 SourceIndex,
                                                               USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    if (Source && !Source->IsSlotEmpty(SourceIndex) && Destination && Destination->IsSlotEmpty(DestinationIndex))
    {
        UObject* SourceContent = Source->GetContent(SourceIndex);
        Source->SetContent(SourceIndex, nullptr);
        Destination->SetContent(DestinationIndex, SourceContent);
    }
}

void USlotManagerComponentBase::SwapContent_Implementation(USlotManagerComponentBase* Source, int32 SourceIndex,
    USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    if (Source && Destination)
    {
        if (!Source->IsSlotEmpty(SourceIndex) && Destination->IsSlotEmpty(DestinationIndex))
        {
            TransferContent(Source, SourceIndex, Destination, DestinationIndex);
        }
        else if (Source->IsSlotEmpty(SourceIndex) && !Destination->IsSlotEmpty(DestinationIndex))
        {
            TransferContent(Destination, DestinationIndex, Source, SourceIndex);
        }
        else if (!Source->IsSlotEmpty(SourceIndex) && !Destination->IsSlotEmpty(DestinationIndex))
        {
            UObject* SourceContent = Source->GetContent(SourceIndex);
            UObject* DestinationContent = Destination->GetContent(DestinationIndex);
            Source->SetContent(SourceIndex, DestinationContent);
            Destination->SetContent(DestinationIndex, SourceContent);
        }
    }
}

void USlotManagerComponentBase::SyncContent_Implementation(USlotManagerComponentBase* Source, int32 SourceIndex,
    USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    if (Source && !Source->IsSlotEmpty(SourceIndex) && Destination && Destination->IsSlotEmpty(DestinationIndex))
    {
        UObject* Content = Source->GetContent(DestinationIndex);
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

bool USlotManagerComponentBase::CheckContent(UObject* Content) const
{
    if (Content == nullptr || !Content->Implements<UDataInstanceInterface>()) return false;

    UDataAsset* Data = GetDataFromContent(Content);
    if (!CheckData(Data)) return false;

    for (auto UsingInstanceInterface : UsingInstanceInterfaces)
    {
        if (UsingInstanceInterface && !Content->GetClass()->ImplementsInterface(UsingInstanceInterface))
        {
            return false;
        }
    }

    return true;
}

bool USlotManagerComponentBase::CheckData(UDataAsset* Data) const
{
    if (Data == nullptr || !Data->Implements<UDataInterface>()) return false;

    for (auto UsingDataInterface : UsingDataInterfaces)
    {
        if (UsingDataInterface && !Data->GetClass()->ImplementsInterface(UsingDataInterface))
        {
            return false;
        }
    }

    return true;
}

UDataAsset* USlotManagerComponentBase::GetDataFromContent(UObject* InContent) const
{
    return InContent && InContent->Implements<UDataInstanceInterface>() ? IDataInstanceInterface::Execute_GetData(InContent) : nullptr;
}

void USlotManagerComponentBase::HandleOnSlotUpdated(int32 Index)
{
    LOG_ACTOR_COMPONENT(Log, TEXT("SlotUpdated: %d"), Index)
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

    TMap<int32, TObjectPtr<UObject>> OldSlotMap = SlotMap;

    MappingSlots();

    for (int32 Index : UpdatedSlotIndices)
    {
        OnSlotUpdated.Broadcast(Index);
    }
}
