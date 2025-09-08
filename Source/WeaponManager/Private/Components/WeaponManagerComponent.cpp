// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "Data/WeaponInstance.h"
#include "GameplayTags/WeaponGameplayTags.h"
#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Objects/SlotContent.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;

    UsingDataInterfaces.Emplace(UWeaponDataInterface::StaticClass());
    UsingInstanceInterfaces.Emplace(UWeaponInstanceInterface::StaticClass());

    SlotConfig.Emplace(Weapon::Slot::Primary, 1);
}

void UWeaponManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindMesh();
}

AActor* UWeaponManagerComponent::GetCurrentWeaponActor() const
{
    USlotContent* CurrentContent = GetContent(CurrentSlotIndex);
    if (CheckContent(CurrentContent))
    {
        AActor* Actor = IWeaponInstanceInterface::Execute_GetActor(CurrentContent);

        return Actor;
    }

    return nullptr;
}

void UWeaponManagerComponent::SetWeaponSlotIndex_Implementation(FWeaponSlotIndex NewWeaponSlotIndex, bool bForce)
{
    int32 NewIndex = GetIndex(NewWeaponSlotIndex);
    SetSlotIndex(NewIndex, bForce);
}

void UWeaponManagerComponent::SetSlotIndex_Implementation(int32 NewSlotIndex, bool bForce)
{
    if (!SlotMap.Contains(NewSlotIndex)) return;
    if (!bForce && CurrentSlotIndex == NewSlotIndex) return;

    int32 OldIndex = CurrentSlotIndex;
    CurrentSlotIndex = NewSlotIndex;

    USlotContent* OldContent = GetContent(OldIndex);
    UnEquip(OldContent);

    USlotContent* NewContent = GetContent(NewSlotIndex);
    Equip(NewContent);
}

bool UWeaponManagerComponent::DoesSocketExist(FName SocketName) const
{
    return Mesh.IsValid() && Mesh->DoesSocketExist(SocketName);
}

bool UWeaponManagerComponent::DoesEmptySlotExist(FGameplayTag SlotType) const
{
    for (const auto& [SlotIndex, Index] : SlotIndexMap)
    {
        if (SlotIndex.Type == SlotType && IsEmpty(Index))
        {
            return true;
        }
    }

    return false;
}

bool UWeaponManagerComponent::CanAddWeaponFromData(UDataAsset* NewData) const
{
    if (CheckData(NewData))
    {
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(NewData);

        return DoesEmptySlotExist(SlotType);
    }

    return false;
}

void UWeaponManagerComponent::AddWeaponFromData(UDataAsset* NewData)
{
    if (CanAddWeaponFromData(NewData))
    {
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(NewData);

        for (auto& [SlotIndex, Index] : SlotIndexMap)
        {
            if (IsEmpty(Index) && SlotIndex.Type == SlotType)
            {
                if (AActor* Actor = SpawnActorFromData(NewData))
                {
                    USlotContent* NewContent = IWeaponActorInterface::Execute_GetInstance(Actor);
                    SetContent(Index, NewContent);

                    break;
                }
            }
        }
    }
}

void UWeaponManagerComponent::CreateSlots()
{
    int32 SlotIndex = -1;
    for (const auto& [SlotType, MaxNum] : SlotConfig)
    {
        for (int32 Index = 0; Index < MaxNum; ++Index)
        {
            ++SlotIndex;

            SlotIndexMap.Emplace(FWeaponSlotIndex(SlotType, Index), SlotIndex);
            Slots.Emplace(SlotIndex, nullptr);
        }
    }

    MaxSlotNum = SlotIndex + 1;
}

bool UWeaponManagerComponent::CheckData(UDataAsset* Data) const
{
    if (Super::CheckData(Data))
    {
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(Data);
        const TSubclassOf<AActor> WeaponActorClass = IWeaponDataInterface::Execute_GetActorClass(Data);
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(Data);

        return SlotConfig.Contains(SlotType) && WeaponActorClass && DoesSocketExist(ActiveSocketName);
    }

    return false;
}

void UWeaponManagerComponent::HandleOnSlotUpdated(int32 Index, USlotContent* OldContent, USlotContent* NewContent)
{
    Super::HandleOnSlotUpdated(Index, OldContent, NewContent);

    if (Index == CurrentSlotIndex)
    {
        Equip(NewContent);
    }
    else
    {
        UnEquip(NewContent);
    }
}

int32 UWeaponManagerComponent::GetIndex(const FWeaponSlotIndex& SlotIndex)
{
    return SlotIndexMap.Contains(SlotIndex) ? SlotIndexMap[SlotIndex] : -1;
}

void UWeaponManagerComponent::FindMesh()
{
    if (!Mesh.IsValid())
    {
        Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
    }
}

bool UWeaponManagerComponent::AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const
{
    bool bResult = false;

    if (WeaponActor)
    {
        if (Mesh.IsValid() && Mesh->DoesSocketExist(SocketName))
        {
            FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(
                EAttachmentRule::SnapToTarget,
                EAttachmentRule::SnapToTarget,
                EAttachmentRule::KeepWorld,
                true);

            bResult = WeaponActor->AttachToComponent(Mesh.Get(), AttachmentTransformRules, SocketName);
        }

        WeaponActor->SetActorHiddenInGame(!bResult);
    }

    return bResult;
}

AActor* UWeaponManagerComponent::SpawnActorFromContent(USlotContent* Content)
{
    if (CheckContent(Content))
    {
        UDataAsset* WeaponData = Content->GetData();
        TSubclassOf<AActor> ActorClass = IWeaponDataInterface::Execute_GetActorClass(WeaponData);

        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Owner = GetOwner();
        ActorSpawnParameters.Instigator = GetOwner()->GetInstigator();
        ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        const FVector SpawnLocation = GetOwner()->GetActorLocation();
        if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters))
        {
            IWeaponActorInterface::Execute_SetInstance(SpawnedActor, Content);

            if (CheckActor(SpawnedActor))
            {
                IWeaponInstanceInterface::Execute_SetActor(Content, SpawnedActor);
                return SpawnedActor;
            }
            else
            {
                SpawnedActor->Destroy();
            }
        }
    }

    return nullptr;
}

bool UWeaponManagerComponent::CheckActor(AActor* Actor) const
{
    if (Actor && Actor->Implements<UWeaponActorInterface>())
    {
        return CheckContent(IWeaponActorInterface::Execute_GetInstance(Actor));
    }

    return false;
}

bool UWeaponManagerComponent::CheckActorClass(TSubclassOf<AActor> ActorClass)
{
    return ActorClass && ActorClass->ImplementsInterface(UWeaponActorInterface::StaticClass());
}

void UWeaponManagerComponent::Equip(USlotContent* Content)
{
    if (CheckContent(Content))
    {
        AActor* Actor = IWeaponInstanceInterface::Execute_GetActor(Content);
        UDataAsset* WeaponData = Content->GetData();
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(WeaponData);

        AttachWeaponActorToSocket(Actor, ActiveSocketName);
    }
}

void UWeaponManagerComponent::UnEquip(USlotContent* Content)
{
    if (CheckContent(Content))
    {
        AActor* Actor = IWeaponInstanceInterface::Execute_GetActor(Content);
        UDataAsset* WeaponData = Content->GetData();
        const FName InActiveSocketName = IWeaponDataInterface::Execute_GetInActiveSocketName(WeaponData);

        AttachWeaponActorToSocket(Actor, InActiveSocketName);
    }
}
