﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "Actors/SocketMeshActor.h"
#include "Actors/SocketSkeletalMeshActor.h"
#include "Actors/SocketStaticMeshActor.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

USocketManagerComponent::USocketManagerComponent()
{
    SetIsReplicatedByDefault(true);
    OverrideBodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void USocketManagerComponent::PostInitProperties()
{
    Super::PostInitProperties();

    Refresh();
}

void USocketManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    FindTargetMesh();
}

void USocketManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, SocketActorSlots);
}

void USocketManagerComponent::SetTargetMesh(UMeshComponent* InTargetMesh)
{
    if (TargetMesh.IsValid()) return;

    TargetMesh = InTargetMesh;
}

bool USocketManagerComponent::AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor)
{
    // 실행 가능 여부 확인
    if (bool bCanAttach = Actor && IsSocketValid(SocketTag) && IsSocketEmpty(SocketTag); !bCanAttach) return false;

    // 액터 부착
    Actor->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), GetSocketName(SocketTag));

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
    auto SocketActor = GetActorByTag(SocketTag);
    if (SocketActor == nullptr) return nullptr;

    // 액터 탈착
    SocketActor->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));

    // 액터 등록 해제
    UnRegisterSocketActor(SocketTag);

    return SocketActor;
}

bool USocketManagerComponent::SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass)
{
    // 실행 가능 여부 확인
    if (bool bCanSpawn = ActorClass && IsSocketValid(SocketTag); !bCanSpawn) return false;

    // 액터 스폰
    AActor* SpawnedActor = SpawnActor(ActorClass);
    if (SpawnedActor == nullptr) return false;

    // 액터 부착
    bool bSucceed = AttachActorToSocket(SocketTag, SpawnedActor);
    if (!bSucceed) SpawnedActor->Destroy();

    return bSucceed;
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
    // 실행 가능 여부 확인
    if (bool bCanSpawn = Mesh && IsSocketValid(SocketTag); !bCanSpawn) return false;

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

void USocketManagerComponent::FindTargetMesh()
{
    if (auto OwnerCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetTargetMesh(OwnerCharacter->GetMesh());
    }
    else
    {
        SetTargetMesh(GetOwner()->GetComponentByClass<UMeshComponent>());
    }
}

void USocketManagerComponent::Refresh()
{
    SocketActorMap.Empty(SocketNameMap.Num());
    for (const auto& [SocketTag, Actor] : SocketActorSlots)
    {
        SocketActorMap.Emplace(SocketTag, Actor);
    }
}

void USocketManagerComponent::RegisterSocketActor(const FGameplayTag& SocketTag, AActor* Actor)
{
    // 실행 가능 여부 확인
    if (bool bCanRegister = Actor && IsSocketValid(SocketTag) && IsSocketEmpty(SocketTag); !bCanRegister) return;

    // 배열에 등록
    SocketActorSlots.Emplace(FSocketActorSlot(SocketTag, Actor));

    // 맵에 등록
    SocketActorMap.Emplace(SocketTag, Actor);
}

void USocketManagerComponent::UnRegisterSocketActor(const FGameplayTag& SocketTag)
{
    // 실행 가능 여부 확인
    if (bool bCanUnRegister = IsSocketValid(SocketTag) && !IsSocketEmpty(SocketTag); !bCanUnRegister) return;

    // 배열로부터 등록 해제
    for (int32 Index = SocketActorSlots.Num() - 1; Index >= 0; --Index)
    {
        if (SocketActorSlots[Index].SocketTag == SocketTag)
        {
            SocketActorSlots.RemoveAt(Index);
            break;
        }
    }

    // 맵으로부터 등록 해제
    SocketActorMap.Remove(SocketTag);
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

void USocketManagerComponent::OnRep_SocketActorSlots(const TArray<FSocketActorSlot>& OldSocketActorSlots)
{
    Refresh();
}
