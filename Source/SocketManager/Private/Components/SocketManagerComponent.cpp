// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "Actors/SocketMeshActor.h"
#include "Actors/SocketSkeletalMeshActor.h"
#include "Actors/SocketStaticMeshActor.h"
#include "GameFramework/Character.h"
#include "GameplayTags/SocketGameplayTags.h"
#include "Net/UnrealNetwork.h"

USocketManagerComponent::USocketManagerComponent()
{
    bWantsInitializeComponent = true;

    SetIsReplicatedByDefault(true);
    OverrideBodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    SocketNameMap.Emplace(Socket::Character::RightHand, FName("hand_r"));
}

void USocketManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindTargetMesh();
}

void USocketManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Slots);
}

void USocketManagerComponent::SetTargetMesh(UMeshComponent* InTargetMesh)
{
    TargetMesh = InTargetMesh;
}

bool USocketManagerComponent::AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor)
{
    if (!Actor || !SocketTag.IsValid()) return false;

    // 액터 부착
    Actor->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true), GetSocketName(SocketTag));

    // 소켓 존재 여부에 따라 액터 표시 혹은 숨기기
    if (DoesSocketExist(SocketTag))
    {
        Actor->SetActorHiddenInGame(false);
    }
    else
    {
        Actor->SetActorHiddenInGame(true);
    }

    // 액터 등록
    RegisterSocketActor(SocketTag, Actor);

    return true;
}

AActor* USocketManagerComponent::DetachActorFromSocket(const FGameplayTag& SocketTag)
{
    // 실행 가능 여부 확인
    auto SocketActor = GetActorBySocketTag(SocketTag);
    if (SocketActor == nullptr) return nullptr;

    // 액터 탈착
    SocketActor->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));

    // 액터 등록 해제
    UnRegisterSocketActor(SocketTag);

    return SocketActor;
}

void USocketManagerComponent::DestroyActorFromSocket(FGameplayTag SocketTag)
{
    if (AActor* DetachedActor = DetachActorFromSocket(SocketTag))
    {
        DetachedActor->Destroy();
    }
}

AActor* USocketManagerComponent::SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass)
{
    AActor* SpawnedActor = SpawnActor(ActorClass);
    if (SpawnedActor && !AttachActorToSocket(SocketTag, SpawnedActor))
    {
        SpawnedActor->Destroy();
        SpawnedActor = nullptr;
    }

    return SpawnedActor;
}

bool USocketManagerComponent::SpawnSkeletalMeshToSocket(const FGameplayTag& SocketTag, USkeletalMesh* SkeletalMesh)
{
    return SpawnMeshToSocket(SocketTag, SkeletalMesh);
}

bool USocketManagerComponent::SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh)
{
    return SpawnMeshToSocket(SocketTag, StaticMesh);
}

bool USocketManagerComponent::SpawnMeshToSocket(const FGameplayTag& SocketTag, UStreamableRenderAsset* Mesh)
{
    if (!Mesh || !SocketTag.IsValid()) return false;

    // 액터 스폰
    TSubclassOf<ASocketMeshActor> SocketMeshActorClass;
    if (Mesh->GetClass() == USkeletalMesh::StaticClass())
    {
        SocketMeshActorClass = ASocketSkeletalMeshActor::StaticClass();
    }
    else if (Mesh->GetClass() == UStaticMesh::StaticClass())
    {
        SocketMeshActorClass = ASocketStaticMeshActor::StaticClass();
    }
    else
    {
        return false;
    }

    auto SpawnedActor = SpawnActor<ASocketMeshActor>(SocketMeshActorClass);
    SpawnedActor->SetBodyInstance(OverrideBodyInstance);
    SpawnedActor->SetMesh(Mesh);

    // 액터 부착
    bool bSucceed = AttachActorToSocket(SocketTag, SpawnedActor);
    if (!bSucceed) SpawnedActor->Destroy();

    return bSucceed;
}

void USocketManagerComponent::SwapSockets(const FGameplayTag& SourceTag, const FGameplayTag& DestinationTag)
{
    AActor* SourceActor = DetachActorFromSocket(SourceTag);
    AActor* DestinationActor = DetachActorFromSocket(DestinationTag);

    AttachActorToSocket(DestinationTag, SourceActor);
    AttachActorToSocket(SourceTag, DestinationActor);
}

void USocketManagerComponent::ClearSocket(const FGameplayTag& SourceTag)
{
    AActor* SocketActor = DetachActorFromSocket(SourceTag);
    if (SocketActor) SocketActor->Destroy();
}

const FSocketSlot& USocketManagerComponent::GetSlotBySocketTag(FGameplayTag SocketTag) const
{
    if (!SocketTag.IsValid()) return FSocketSlot::EmptySlot;

    for (const FSocketSlot& Slot : Slots)
    {
        if (Slot.SocketTag == SocketTag)
        {
            return Slot;
        }
    }

    return FSocketSlot::EmptySlot;
}

const FSocketSlot& USocketManagerComponent::GetSlotByActor(AActor* Actor) const
{
    if (!Actor) return FSocketSlot::EmptySlot;

    for (const FSocketSlot& Slot : Slots)
    {
        if (Slot.Actor == Actor)
        {
            return Slot;
        }
    }

    return FSocketSlot::EmptySlot;
}

AActor* USocketManagerComponent::GetActorBySocketTag(const FGameplayTag& SocketTag) const
{
    const FSocketSlot& Slot = GetSlotBySocketTag(SocketTag);

    return Slot.Actor;
}

FGameplayTag USocketManagerComponent::GetSocketTagByActor(AActor* Actor) const
{
    const FSocketSlot& Slot = GetSlotByActor(Actor);

    return Slot.SocketTag;
}

void USocketManagerComponent::FindTargetMesh()
{
    if (TargetMesh.IsValid()) return;

    if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetTargetMesh(OwningCharacter->GetMesh());
    }
    else
    {
        SetTargetMesh(GetOwner()->GetComponentByClass<UMeshComponent>());
    }
}

void USocketManagerComponent::RegisterSocketActor(const FGameplayTag& SocketTag, AActor* Actor)
{
    if (Actor && DoesSocketExist(SocketTag))
    {
        Slots.Emplace(FSocketSlot(SocketTag, Actor));
    }
}

void USocketManagerComponent::UnRegisterSocketActor(const FGameplayTag& SocketTag)
{
    if (!SocketTag.IsValid()) return;

    // 배열로부터 등록 해제
    for (int32 Index = Slots.Num() - 1; Index >= 0; --Index)
    {
        if (Slots[Index].SocketTag == SocketTag)
        {
            Slots.RemoveAt(Index);
            break;
        }
    }
}

AActor* USocketManagerComponent::SpawnActor(TSubclassOf<AActor> ActorClass)
{
    // 입력 유효성 검사
    if (ActorClass == nullptr) return nullptr;

    // 유효성 검사
    UWorld* World = GetWorld();
    AActor* Owner = GetOwner();
    if (World == nullptr || Owner == nullptr) return nullptr;

    // ActorSpawnParameters 설정
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.Owner = Owner;
    ActorSpawnParameters.Instigator = Owner->GetInstigator();
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 액터 스폰
    const FVector SpawnLocation = Owner->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);
    SpawnedActor->SetReplicates(ShouldReplicate());

    return SpawnedActor;
}

AActor* USocketManagerComponent::SpawnActorDeferred(TSubclassOf<AActor> ActorClass)
{
    // 입력 유효성 검사
    if (ActorClass == nullptr) return nullptr;

    // 유효성 검사
    UWorld* World = GetWorld();
    AActor* Owner = GetOwner();
    if (World == nullptr || Owner == nullptr) return nullptr;

    // 액터 스폰
    FTransform SpawnTransform = FTransform(Owner->GetActorLocation());
    AActor* SpawnedActor = World->SpawnActorDeferred<AActor>(ActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    SpawnedActor->SetReplicates(ShouldReplicate());

    return SpawnedActor;
}

void USocketManagerComponent::OnRep_Slots(const TArray<FSocketSlot>& OldSlots)
{

}
