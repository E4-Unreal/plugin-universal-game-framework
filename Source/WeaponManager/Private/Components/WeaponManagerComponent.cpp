// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "Data/DataDefinitionBase.h"
#include "Data/WeaponInstance.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "FunctionLibraries/WeaponDataFunctionLibrary.h"
#include "GameplayTags/WeaponGameplayTags.h"
#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;

    SlotConfig.Emplace(Weapon::Slot::Primary, 1);
}

void UWeaponManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindMesh();
}

int32 UWeaponManagerComponent::GetEmptySlotIndex(UDataInstanceBase* NewContent) const
{
    if (CheckContent(NewContent))
    {
        const FGameplayTag SlotType = UWeaponDataFunctionLibrary::GetSlotType(NewContent->Definition);

        for (const auto& [SlotIndex, Index] : SlotIndexMap)
        {
            if (SlotIndex.Type == SlotType && IsSlotEmpty(Index))
            {
                return Index;
            }
        }
    }

    return -1;
}

AActor* UWeaponManagerComponent::GetCurrentWeaponActor() const
{
    UDataInstanceBase* CurrentContent = GetContent(CurrentSlotIndex);
    if (CheckContent(CurrentContent))
    {
        AActor* Actor = UWeaponDataFunctionLibrary::GetActor(CurrentContent);

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

    UDataInstanceBase* OldContent = GetContent(OldIndex);
    UnEquip(OldContent);

    UDataInstanceBase* NewContent = GetContent(NewSlotIndex);
    Equip(NewContent);
}

bool UWeaponManagerComponent::DoesSocketExist(FName SocketName) const
{
    return Mesh.IsValid() && Mesh->DoesSocketExist(SocketName);
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

bool UWeaponManagerComponent::CheckData(UDataDefinitionBase* Definition) const
{
    if (Super::CheckData(Definition))
    {
        if (UWeaponDataFunctionLibrary::HasWeaponData(Definition))
        {
            const FGameplayTag SlotType = UWeaponDataFunctionLibrary::GetSlotType(Definition);
            const TSubclassOf<AActor> WeaponActorClass = UWeaponDataFunctionLibrary::GetActorClass(Definition);
            const FName ActiveSocketName = UWeaponDataFunctionLibrary::GetActiveSocketName(Definition);

            return SlotConfig.Contains(SlotType) && WeaponActorClass && DoesSocketExist(ActiveSocketName);
        }
    }

    return false;
}

bool UWeaponManagerComponent::CheckContent(UDataInstanceBase* Content) const
{
    if (Super::CheckContent(Content))
    {
        if (UWeaponDataFunctionLibrary::HasWeaponInstance(Content) && UWeaponDataFunctionLibrary::HasWeaponData(Content->Definition))
        {
            const float MaxDurability = UWeaponDataFunctionLibrary::GetMaxDurability(Content->Definition);
            const float Durability = UWeaponDataFunctionLibrary::GetDurability(Content);

            return MaxDurability > 0.0f ? Durability > 0.0f : true;
        }
    }

    return false;
}

void UWeaponManagerComponent::HandleOnSlotUpdated(int32 Index)
{
    Super::HandleOnSlotUpdated(Index);

    auto Content = GetContent(Index);
    if (Index == CurrentSlotIndex)
    {
        Equip(Content);
    }
    else
    {
        UnEquip(Content);
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

AActor* UWeaponManagerComponent::SpawnActorFromData(UDataDefinitionBase* Definition)
{
    if (CheckData(Definition))
    {
        UDataInstanceBase* NewContent = UDataManagerFunctionLibrary::CreateDataInstance(Definition);
        return SpawnActorFromContent(NewContent);
    }

    return nullptr;
}

AActor* UWeaponManagerComponent::SpawnActorFromContent(UDataInstanceBase* Content)
{
    if (CheckContent(Content))
    {
        if (UWeaponDataFunctionLibrary::HasWeaponData(Content->Definition))
        {
            TSubclassOf<AActor> ActorClass = UWeaponDataFunctionLibrary::GetActorClass(Content->Definition);

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
                    UWeaponDataFunctionLibrary::SetActor(Content, SpawnedActor);
                    return SpawnedActor;
                }
                else
                {
                    SpawnedActor->Destroy();
                }
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

void UWeaponManagerComponent::Equip(UDataInstanceBase* Content)
{
    if (CheckContent(Content))
    {
        AActor* Actor = UWeaponDataFunctionLibrary::GetActor(Content);
        if (Actor == nullptr) Actor = SpawnActorFromContent(Content);
        const FName ActiveSocketName = UWeaponDataFunctionLibrary::GetActiveSocketName(Content->Definition);

        AttachWeaponActorToSocket(Actor, ActiveSocketName);
    }
}

void UWeaponManagerComponent::UnEquip(UDataInstanceBase* Content)
{
    if (CheckContent(Content))
    {
        AActor* Actor = UWeaponDataFunctionLibrary::GetActor(Content);
        const FName InActiveSocketName = UWeaponDataFunctionLibrary::GetInActiveSocketName(Content->Definition);

        AttachWeaponActorToSocket(Actor, InActiveSocketName);
    }
}
