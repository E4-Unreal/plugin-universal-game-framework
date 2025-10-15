// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "GameFramework/Character.h"
#include "GameplayTags/SocketGameplayTags.h"


USocketManagerComponent::USocketManagerComponent()
{
    FSocketSlotConfig HeadSocketSlotConfig;
    HeadSocketSlotConfig.SocketTag = Socket::Character::Head;
    SlotConfigs.Emplace(HeadSocketSlotConfig);

    FSocketSlotConfig UpperBodySocketSlotConfig;
    UpperBodySocketSlotConfig.SocketTag = Socket::Character::UpperBody;
    SlotConfigs.Emplace(UpperBodySocketSlotConfig);

    FSocketSlotConfig LowerBodySocketSlotConfig;
    LowerBodySocketSlotConfig.SocketTag = Socket::Character::LowerBody;
    SlotConfigs.Emplace(LowerBodySocketSlotConfig);

    FSocketSlotConfig HandSocketSlotConfig;
    HandSocketSlotConfig.SocketTag = Socket::Character::Hand;
    SlotConfigs.Emplace(HandSocketSlotConfig);

    FSocketSlotConfig FootSocketSlotConfig;
    FootSocketSlotConfig.SocketTag = Socket::Character::Foot;
    SlotConfigs.Emplace(FootSocketSlotConfig);

    FSocketSlotConfig RightHandSocketSlotConfig;
    RightHandSocketSlotConfig.SocketTag = Socket::Character::RightHand;
    RightHandSocketSlotConfig.DefaultSocketName = "hand_r";
    SlotConfigs.Emplace(RightHandSocketSlotConfig);

    FSocketSlotConfig LeftHandSocketSlotConfig;
    LeftHandSocketSlotConfig.SocketTag = Socket::Character::LeftHand;
    LeftHandSocketSlotConfig.DefaultSocketName = "hand_l";
    SlotConfigs.Emplace(LeftHandSocketSlotConfig);
}

void USocketManagerComponent::OnRegister()
{
    Super::OnRegister();

    FindRootMesh();
    InitializeSlots();
}

void USocketManagerComponent::SetRootMesh(UMeshComponent* NewRootMesh)
{
    RootMesh = NewRootMesh;
}

void USocketManagerComponent::ResetSlot(FGameplayTag InSocketTag)
{
    if (HasSlot(InSocketTag))
    {
        ClearSlot(InSocketTag);
        ApplySlotConfig(GetSlotConfig(InSocketTag));
    }
}

UStaticMeshComponent* USocketManagerComponent::SetStaticMesh(UStaticMesh* NewStaticMesh, FGameplayTag SocketTag, FName SocketName, FGameplayTagContainer SocketTagsToHide)
{
    if (!RootMesh.IsValid() || !HasSlot(SocketTag)) return nullptr;

    // 초기화
    ClearSlot(SocketTag);

    // SlotConfig 가져오기
    const auto& SlotConfig = GetSlotConfig(SocketTag);
    if (!NewStaticMesh) NewStaticMesh = SlotConfig.DefaultStaticMesh;
    if (SocketName.IsNone()) SocketName = SlotConfig.DefaultSocketName;

    // Slot 설정
    auto& Slot = GetSlotRef(SocketTag);
    Slot.SocketName = SocketName;

    if (!SocketTagsToHide.IsEmpty())
    {
        Slot.SocketTagsToHide = SocketTagsToHide;
        HideSockets(SocketTagsToHide);
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

USkeletalMeshComponent* USocketManagerComponent::SetSkeletalMesh(USkeletalMesh* NewSkeletalMesh, FGameplayTag SocketTag, FName SocketName, FGameplayTagContainer SocketTagsToHide)
{
    if (!RootMesh.IsValid() || !HasSlot(SocketTag)) return nullptr;

    // 초기화
    ClearSlot(SocketTag);

    // SlotConfig 가져오기
    const auto& SlotConfig = GetSlotConfig(SocketTag);
    if (!NewSkeletalMesh) NewSkeletalMesh = SlotConfig.DefaultSkeletalMesh;
    if (SocketName.IsNone()) SocketName = SlotConfig.DefaultSocketName;

    // 모듈러 여부 확인
    bool bModular = IsModular(NewSkeletalMesh);
    SocketName = bModular ? NAME_None : SocketName;

    // Slot 설정
    auto& Slot = GetSlotRef(SocketTag);
    Slot.SocketName = SocketName;

    if (!SocketTagsToHide.IsEmpty())
    {
        Slot.SocketTagsToHide = SocketTagsToHide;
        HideSockets(SocketTagsToHide);
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

AActor* USocketManagerComponent::SetActor(TSubclassOf<AActor> NewActorClass, FGameplayTag SocketTag, FName SocketName, FGameplayTagContainer SocketTagsToHide)
{
    if (!RootMesh.IsValid() || !HasSlot(SocketTag)) return nullptr;

    // 초기화
    ClearSlot(SocketTag);

    // SlotConfig 가져오기
    const auto& SlotConfig = GetSlotConfig(SocketTag);
    if (!NewActorClass) NewActorClass = SlotConfig.DefaultActorClass;
    if (SocketName.IsNone()) SocketName = SlotConfig.DefaultSocketName;

    // Slot 설정
    auto& Slot = GetSlotRef(SocketTag);
    Slot.SocketName = SocketName;

    if (!SocketTagsToHide.IsEmpty())
    {
        Slot.SocketTagsToHide = SocketTagsToHide;
        HideSockets(SocketTagsToHide);
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

void USocketManagerComponent::SetMaterial(FGameplayTag SocketTag, UMaterialInterface* Material, int32 Index)
{
    if (!HasSlot(SocketTag)) return;

    const auto& Slot = GetSlot(SocketTag);
    if (Slot.StaticMeshComponent)
    {
        Slot.StaticMeshComponent->SetMaterial(Index, Material);
    }
    else if (Slot.SkeletalMeshComponent)
    {
        Slot.SkeletalMeshComponent->SetMaterial(Index, Material);
    }
}

void USocketManagerComponent::SetMaterialByName(FGameplayTag SocketTag, UMaterialInterface* Material, FName SlotName)
{
    if (!HasSlot(SocketTag)) return;

    const auto& Slot = GetSlot(SocketTag);
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

void USocketManagerComponent::InitializeSlots()
{
    // 슬롯 생성
    for (const auto& SlotConfig : SlotConfigs)
    {
        if (!SlotConfig.IsValid()) continue;

        FSocketSlot NewSlot;
        NewSlot.SocketTag = SlotConfig.SocketTag;

        Slots.Emplace(NewSlot);
    }

    // 슬롯 기본값 설정
    for (const auto& SlotConfig : SlotConfigs)
    {
        ApplySlotConfig(SlotConfig);
    }
}

bool USocketManagerComponent::HasSlot(FGameplayTag InSocketTag) const
{
    bool bResult = false;

    for (const auto& Slot : Slots)
    {
        if (Slot.SocketTag == InSocketTag)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

const FSocketSlot& USocketManagerComponent::GetSlot(FGameplayTag InSocketTag) const
{
    for (const auto& Slot : Slots)
    {
        if (Slot.SocketTag == InSocketTag)
        {
            return Slot;
        }
    }

    return FSocketSlot::EmptySlot;
}

FSocketSlot& USocketManagerComponent::GetSlotRef(FGameplayTag InSocketTag)
{
    return const_cast<FSocketSlot&>(GetSlot(InSocketTag));
}

void USocketManagerComponent::ClearSlot(FGameplayTag InSocketTag)
{
    if (HasSlot(InSocketTag))
    {
        auto& Slot = GetSlotRef(InSocketTag);
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

        if (!Slot.SocketTagsToHide.IsEmpty())
        {
            ShowSockets(Slot.SocketTagsToHide);

            Slot.SocketTagsToHide.Reset();
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

const FSocketSlotConfig& USocketManagerComponent::GetSlotConfig(FGameplayTag InSocketTag) const
{
    for (const auto& SlotConfig : SlotConfigs)
    {
        if (SlotConfig.SocketTag == InSocketTag)
        {
            return SlotConfig;
        }
    }

    return FSocketSlotConfig::EmptySlotConfig;
}

void USocketManagerComponent::ApplySlotConfig(const FSocketSlotConfig& InSlotConfig)
{
    if (InSlotConfig.IsValid())
    {
        auto SocketTag = InSlotConfig.SocketTag;
        auto SocketName = InSlotConfig.DefaultSocketName;
        auto DefaultStaticMesh = InSlotConfig.DefaultStaticMesh;
        auto DefaultSkeletalMesh = InSlotConfig.DefaultSkeletalMesh;
        auto DefaultActorClass = InSlotConfig.DefaultActorClass;

        if (DefaultActorClass)
        {
            SetActor(DefaultActorClass, SocketTag, SocketName);
        }
        else if (DefaultSkeletalMesh)
        {
            SetSkeletalMesh(DefaultSkeletalMesh, SocketTag, SocketName);
        }
        else if (DefaultStaticMesh)
        {
            SetStaticMesh(DefaultStaticMesh, SocketTag, SocketName);
        }
    }
}

void USocketManagerComponent::ShowSockets(const FGameplayTagContainer& SocketTagsToHide)
{
    for (const auto& SocketTagToHide : SocketTagsToHide)
    {
        auto& Slot = GetSlotRef(SocketTagToHide);
        Slot.HiddenBySocketTags.RemoveTag(SocketTagToHide);
        if (Slot.HiddenBySocketTags.IsEmpty())
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

void USocketManagerComponent::HideSockets(const FGameplayTagContainer& SocketTagsToHide)
{
    for (const auto& SocketTagToHide : SocketTagsToHide)
    {
        auto& Slot = GetSlotRef(SocketTagToHide);
        Slot.HiddenBySocketTags.AddTag(SocketTagToHide);
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
