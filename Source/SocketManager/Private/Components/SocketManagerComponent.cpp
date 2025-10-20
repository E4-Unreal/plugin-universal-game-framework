// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "GameFramework/Character.h"
#include "GameplayTags/SocketGameplayTags.h"
#include "Interfaces/SocketDataInterface.h"
#include "Subsystems/DataManagerSubsystem.h"


USocketManagerComponent::USocketManagerComponent()
{
    DataAssetType = "SocketDefinition";

    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::FullBody, 1000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Head, 2000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Hair, 3000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Face, 4000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Ear, 5000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Beard, 6000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::UpperBody, 7000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::LowerBody, 8000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Hand, 9000));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::Foot, 10000));

    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::RightHand, "hand_r"));
    SlotConfigs.Emplace(FSocketSlotConfig(Socket::Character::LeftHand, "hand_l"));
}

void USocketManagerComponent::OnRegister()
{
    Super::OnRegister();

    FindRootMesh();
    CreateSlots();
    ResetSlots();
}

void USocketManagerComponent::SetRootMesh(UMeshComponent* NewRootMesh)
{
    RootMesh = NewRootMesh;
}

void USocketManagerComponent::ResetSlot(FGameplayTag InSocketType)
{
    ClearSlot(InSocketType);
    SetSocketByData(GetDefaultData(InSocketType));
}

UStaticMeshComponent* USocketManagerComponent::SetSocketByStaticMesh(UStaticMesh* NewStaticMesh, FGameplayTag SocketType, FName SocketName, FGameplayTagContainer SocketTypesToHide)
{
    // 유효성 검사
    if (!RootMesh.IsValid() || !NewStaticMesh || !HasSlot(SocketType)) return nullptr;

    // SocketName 설정
    if (SocketName.IsNone()) SocketName = GetDefaultSocketName(SocketType);

    // 초기화
    ClearSlot(SocketType);

    // Slot 설정
    auto& Slot = GetSlotRef(SocketType);
    Slot.SocketName = SocketName;

    if (!SocketTypesToHide.IsEmpty())
    {
        Slot.SocketTypesToHide = SocketTypesToHide;
        HideSockets(SocketType, SocketTypesToHide);
    }

    // StaticMeshComponent 부착
    if (DoesSocketExist(SocketName))
    {
        Slot.StaticMeshComponent = GetOrCreateStaticMeshComponent();
        FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
        Slot.StaticMeshComponent->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
        Slot.StaticMeshComponent->SetStaticMesh(NewStaticMesh);
    }

    return Slot.StaticMeshComponent;
}

USkeletalMeshComponent* USocketManagerComponent::SetSocketBySkeletalMesh(USkeletalMesh* NewSkeletalMesh, FGameplayTag SocketType, FName SocketName, FGameplayTagContainer SocketTypesToHide)
{
    // 유효성 검사
    if (!RootMesh.IsValid() || !NewSkeletalMesh || !HasSlot(SocketType)) return nullptr;

    // SocketName 설정
    if (SocketName.IsNone()) SocketName = GetDefaultSocketName(SocketType);

    // 초기화
    ClearSlot(SocketType);

    // 모듈러 여부 확인
    bool bModular = IsModular(NewSkeletalMesh);
    SocketName = bModular ? NAME_None : SocketName;

    // Slot 설정
    auto& Slot = GetSlotRef(SocketType);
    Slot.SocketName = SocketName;

    if (!SocketTypesToHide.IsEmpty())
    {
        Slot.SocketTypesToHide = SocketTypesToHide;
        HideSockets(SocketType, SocketTypesToHide);
    }

    // SkeletalMeshComponent 부착
    if (bModular || DoesSocketExist(SocketName))
    {
        Slot.SkeletalMeshComponent = GetOrCreateSkeletalMeshComponent();
        FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
        Slot.SkeletalMeshComponent->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
        Slot.SkeletalMeshComponent->SetSkeletalMesh(NewSkeletalMesh);
    }

    return Slot.SkeletalMeshComponent;
}

AActor* USocketManagerComponent::SetSocketByActorClass(TSubclassOf<AActor> NewActorClass, FGameplayTag SocketType, FName SocketName, FGameplayTagContainer SocketTypesToHide)
{
    // 유효성 검사
    if (!RootMesh.IsValid() || !NewActorClass || !HasSlot(SocketType)) return nullptr;

    // SocketName 설정
    if (SocketName.IsNone()) SocketName = GetDefaultSocketName(SocketType);

    // 초기화
    ClearSlot(SocketType);

    // Slot 설정
    auto& Slot = GetSlotRef(SocketType);
    Slot.SocketName = SocketName;

    if (!SocketTypesToHide.IsEmpty())
    {
        Slot.SocketTypesToHide = SocketTypesToHide;
        HideSockets(SocketType, SocketTypesToHide);
    }

    // Actor 부착
    if (DoesSocketExist(SocketName))
    {
        Slot.Actor = SpawnActor(NewActorClass);
        FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
        Slot.Actor->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);

        return Slot.Actor;
    }

    return nullptr;
}

void USocketManagerComponent::SetSocketByData(const TScriptInterface<ISocketDataInterface>& NewData)
{
    if (!CheckData(NewData)) return;

    auto DataObject = NewData.GetObject();
    auto SocketType = ISocketDataInterface::Execute_GetSocketType(DataObject);
    auto SocketName = ISocketDataInterface::Execute_GetSocketName(DataObject);
    auto SocketTypesToHide = ISocketDataInterface::Execute_GetSocketTypesToHide(DataObject);
    auto StaticMesh = ISocketDataInterface::Execute_GetStaticMesh(DataObject);
    auto SkeletalMesh = ISocketDataInterface::Execute_GetSkeletalMesh(DataObject);
    auto ActorClass = ISocketDataInterface::Execute_GetActorClass(DataObject);

    if (!ActorClass.IsNull())
    {
        SetSocketByActorClass(ActorClass.LoadSynchronous(), SocketType, SocketName, SocketTypesToHide);
    }
    else if (!SkeletalMesh.IsNull())
    {
        SetSocketBySkeletalMesh(SkeletalMesh.LoadSynchronous(), SocketType, SocketName, SocketTypesToHide);
    }
    else if (!StaticMesh.IsNull())
    {
        SetSocketByStaticMesh(StaticMesh.LoadSynchronous(), SocketType, SocketName, SocketTypesToHide);
    }
}

void USocketManagerComponent::SetSocketByID(int32 NewID)
{
    SetSocketByData(GetDataByID(NewID));
}

void USocketManagerComponent::SetMaterial(FGameplayTag SocketType, UMaterialInterface* Material, int32 Index)
{
    if (!HasSlot(SocketType)) return;

    const auto& Slot = GetSlot(SocketType);
    if (Slot.StaticMeshComponent)
    {
        Slot.StaticMeshComponent->SetMaterial(Index, Material);
    }
    else if (Slot.SkeletalMeshComponent)
    {
        Slot.SkeletalMeshComponent->SetMaterial(Index, Material);
    }
}

void USocketManagerComponent::SetMaterialByName(FGameplayTag SocketType, UMaterialInterface* Material, FName SlotName)
{
    if (!HasSlot(SocketType)) return;

    const auto& Slot = GetSlot(SocketType);
    if (Slot.StaticMeshComponent)
    {
        Slot.StaticMeshComponent->SetMaterialByName(SlotName, Material);
    }
    else if (Slot.SkeletalMeshComponent)
    {
        Slot.SkeletalMeshComponent->SetMaterialByName(SlotName, Material);
    }
}

void USocketManagerComponent::FindRootMesh()
{
    if (RootMesh.IsValid()) return;

    UMeshComponent* FoundRootMesh = GetOwner()->IsA<ACharacter>()
        ? Cast<ACharacter>(GetOwner())->GetMesh()
        : GetOwner()->GetComponentByClass<UMeshComponent>();

    SetRootMesh(FoundRootMesh);
}

void USocketManagerComponent::CreateSlots()
{
    if (!Slots.IsEmpty()) return;

    for (const auto& SlotConfig : SlotConfigs)
    {
        if (!SlotConfig.IsValid()) continue;

        FSocketSlot NewSlot;
        NewSlot.SocketType = SlotConfig.SocketType;

        Slots.Emplace(NewSlot);
    }
}

void USocketManagerComponent::ResetSlots()
{
    for (const auto& Slot : Slots)
    {
        ResetSlot(Slot.SocketType);
    }
}

bool USocketManagerComponent::CheckData(const TScriptInterface<ISocketDataInterface>& InData) const
{
    return InData.GetObject() && InData.GetObject()->Implements<USocketDataInterface>();
}

bool USocketManagerComponent::HasSlot(FGameplayTag InSocketType) const
{
    bool bResult = false;

    for (const auto& Slot : Slots)
    {
        if (Slot.SocketType == InSocketType)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

const FSocketSlot& USocketManagerComponent::GetSlot(FGameplayTag InSocketType) const
{
    for (const auto& Slot : Slots)
    {
        if (Slot.SocketType == InSocketType)
        {
            return Slot;
        }
    }

    return FSocketSlot::EmptySlot;
}

FSocketSlot& USocketManagerComponent::GetSlotRef(FGameplayTag InSocketType)
{
    return const_cast<FSocketSlot&>(GetSlot(InSocketType));
}

void USocketManagerComponent::ClearSlot(FGameplayTag InSocketType)
{
    if (HasSlot(InSocketType))
    {
        auto& Slot = GetSlotRef(InSocketType);
        if (Slot.StaticMeshComponent)
        {
            ReleaseStaticMeshComponent(Slot.StaticMeshComponent);
            Slot.StaticMeshComponent = nullptr;
        }
        else if (Slot.SkeletalMeshComponent)
        {
            ReleaseSkeletalMeshComponent(Slot.SkeletalMeshComponent);
            Slot.SkeletalMeshComponent = nullptr;
        }
        else if (Slot.Actor)
        {
            Slot.Actor->Destroy();
            Slot.Actor = nullptr;
        }

        if (!Slot.SocketTypesToHide.IsEmpty())
        {
            ShowSockets(InSocketType, Slot.SocketTypesToHide);

            Slot.SocketTypesToHide.Reset();
        }
    }
}

bool USocketManagerComponent::DoesSocketExist(FName InSocketName) const
{
    return RootMesh.IsValid() && RootMesh->DoesSocketExist(InSocketName);
}

bool USocketManagerComponent::IsModular(USkeletalMesh* InSkeletalMesh) const
{
    if (InSkeletalMesh)
    {
        if (auto RootSkeletalMeshComponent = Cast<USkeletalMeshComponent>(RootMesh.Get()))
        {
            if (auto RootSkeletalMesh = RootSkeletalMeshComponent->GetSkeletalMeshAsset())
            {
                if (RootSkeletalMesh->GetSkeleton()->IsCompatibleMesh(InSkeletalMesh))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

UStaticMeshComponent* USocketManagerComponent::GetOrCreateStaticMeshComponent()
{
    UStaticMeshComponent* StaticMeshComponent = nullptr;

    if (StaticMeshComponentPool.IsEmpty())
    {
        if (RootMesh.IsValid())
        {
            StaticMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
            StaticMeshComponent->CreationMethod = EComponentCreationMethod::Instance;
            StaticMeshComponent->SetupAttachment(RootMesh.Get());
            StaticMeshComponent->SetCollisionProfileName(RootMesh->GetCollisionProfileName());
            StaticMeshComponent->RegisterComponent();
        }
    }
    else
    {
        StaticMeshComponent = StaticMeshComponentPool.Pop(EAllowShrinking::No);
        StaticMeshComponent->SetVisibility(true);
    }

    return StaticMeshComponent;
}

void USocketManagerComponent::ReleaseStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent)
{
    if (StaticMeshComponent)
    {
        StaticMeshComponent->SetStaticMesh(nullptr);
        StaticMeshComponent->SetVisibility(false);
        for (int32 Index = 0; Index < StaticMeshComponent->GetMaterialSlotNames().Num(); ++Index)
        {
            StaticMeshComponent->SetMaterial(Index, nullptr);
        }

        StaticMeshComponentPool.Push(StaticMeshComponent);
    }
}

USkeletalMeshComponent* USocketManagerComponent::GetOrCreateSkeletalMeshComponent()
{
    USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

    if (SkeletalMeshComponentPool.IsEmpty())
    {
        if (RootMesh.IsValid())
        {
            SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(GetOwner());
            SkeletalMeshComponent->CreationMethod = EComponentCreationMethod::Instance;
            SkeletalMeshComponent->SetupAttachment(RootMesh.Get());
            SkeletalMeshComponent->SetCollisionProfileName(RootMesh->GetCollisionProfileName());
            SkeletalMeshComponent->SetLeaderPoseComponent(Cast<USkeletalMeshComponent>(RootMesh));
            SkeletalMeshComponent->RegisterComponent();
        }
    }
    else
    {
        SkeletalMeshComponent = SkeletalMeshComponentPool.Pop(EAllowShrinking::No);
        SkeletalMeshComponent->SetVisibility(true);
    }

    return SkeletalMeshComponent;
}

void USocketManagerComponent::ReleaseSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent)
{
    if (SkeletalMeshComponent)
    {
        SkeletalMeshComponent->SetSkeletalMesh(nullptr);
        SkeletalMeshComponent->SetVisibility(false);
        for (int32 Index = 0; Index < SkeletalMeshComponent->GetMaterialSlotNames().Num(); ++Index)
        {
            SkeletalMeshComponent->SetMaterial(Index, nullptr);
        }

        SkeletalMeshComponentPool.Push(SkeletalMeshComponent);
    }
}

AActor* USocketManagerComponent::SpawnActor(TSubclassOf<AActor> InActorClass)
{
    if (GetOwner()->HasAuthority() && InActorClass)
    {
        UWorld* World = GetWorld();
        AActor* Owner = GetOwner();

        // ActorSpawnParameters 설정
        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Owner = Owner;
        ActorSpawnParameters.Instigator = Owner->GetInstigator();
        ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        // 액터 스폰
        const FVector SpawnLocation = Owner->GetActorLocation();
        AActor* SpawnedActor = World->SpawnActor<AActor>(InActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);
        SpawnedActor->SetReplicates(true);

        return SpawnedActor;
    }

    return nullptr;
}

const FSocketSlotConfig& USocketManagerComponent::GetSlotConfig(FGameplayTag InSocketType) const
{
    for (const auto& SlotConfig : SlotConfigs)
    {
        if (SlotConfig.SocketType == InSocketType)
        {
            return SlotConfig;
        }
    }

    return FSocketSlotConfig::EmptySlotConfig;
}

FName USocketManagerComponent::GetDefaultSocketName(FGameplayTag SocketType) const
{
    const auto& SlotConfig = GetSlotConfig(SocketType);

    return SlotConfig.SocketName;
}

UDataAsset* USocketManagerComponent::GetDefaultData(FGameplayTag SocketType) const
{
    const auto& SlotConfig = GetSlotConfig(SocketType);
    auto SocketDefinition = !SlotConfig.SocketDefinition.IsNull() ? SlotConfig.SocketDefinition.LoadSynchronous() : GetDataByID(SlotConfig.ID);

    return SocketDefinition;
}

UDataAsset* USocketManagerComponent::GetDataByID(int32 ID) const
{
    if (auto Subsystem = GEngine->GetEngineSubsystem<UDataManagerSubsystem>())
    {
        auto SocketDefinition = Subsystem->GetDataAsset(DataAssetType, ID);
        if (!SocketDefinition.IsNull())
        {
            return SocketDefinition.LoadSynchronous();
        }
    }

    return nullptr;
}

void USocketManagerComponent::ShowSockets(FGameplayTag HiddenBySocketType, const FGameplayTagContainer& SocketTypesToHide)
{
    for (const auto& SocketTypeToHide : SocketTypesToHide)
    {
        auto& Slot = GetSlotRef(SocketTypeToHide);
        Slot.HiddenBySocketTypes.RemoveTag(HiddenBySocketType);
        if (Slot.HiddenBySocketTypes.IsEmpty())
        {
            if (Slot.StaticMeshComponent)
            {
                Slot.StaticMeshComponent->SetVisibility(true);
            }
            else if (Slot.SkeletalMeshComponent)
            {
                Slot.SkeletalMeshComponent->SetVisibility(true);
            }
            else if (Slot.Actor)
            {
                Slot.Actor->SetHidden(false);
            }
        }
    }
}

void USocketManagerComponent::HideSockets(FGameplayTag HiddenBySocketType, const FGameplayTagContainer& SocketTypesToHide)
{
    for (const auto& SocketTypeToHide : SocketTypesToHide)
    {
        auto& Slot = GetSlotRef(SocketTypeToHide);
        Slot.HiddenBySocketTypes.AddTag(HiddenBySocketType);
        if (Slot.StaticMeshComponent)
        {
            Slot.StaticMeshComponent->SetVisibility(false);
        }
        else if (Slot.SkeletalMeshComponent)
        {
            Slot.SkeletalMeshComponent->SetVisibility(false);
        }
        else if (Slot.Actor)
        {
            Slot.Actor->SetHidden(true);
        }
    }
}
