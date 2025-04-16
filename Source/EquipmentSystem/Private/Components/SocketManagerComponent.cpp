// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "Animation/SkeletalMeshActor.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"

USocketManagerComponent::USocketManagerComponent()
{
    bWantsInitializeComponent = true;

    OverrideBodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void USocketManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    SocketActorMap.Reserve(SocketNameMap.Num());

    if (auto OwnerCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetTargetMesh(OwnerCharacter->GetMesh());
    }
}

void USocketManagerComponent::SetTargetMesh(USkeletalMeshComponent* Value)
{
    if (TargetMesh.IsValid()) return;

    TargetMesh = Value;
}

void USocketManagerComponent::AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor)
{
    // 입력 유효성 검사
    if (Actor == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 부착
    Actor->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), GetSocketName(SocketTag));
    SocketActorMap.Emplace(SocketTag, Actor);
}

void USocketManagerComponent::SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass)
{
    // 입력 유효성 검사
    if (ActorClass == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 스폰
    AActor* SpawnedActor = SpawnActor(ActorClass);
    if (SpawnedActor == nullptr) return;

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
}

void USocketManagerComponent::SpawnSkeletalMeshToSocket(const FGameplayTag& SocketTag, USkeletalMesh* SkeletalMesh,
    TSubclassOf<ASkeletalMeshActor> SkeletalMeshActorClass)
{
    // 입력 유효성 검사
    if (SkeletalMesh == nullptr || !DoesSocketExist(SocketTag)) return;

    // 스켈레탈 메시 액터 스폰
    auto SpawnedActor = SpawnSkeletalMeshActor(SkeletalMesh, SkeletalMeshActorClass);
    SpawnedActor->GetSkeletalMeshComponent()->SetSkeletalMesh(SkeletalMesh);

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
}

void USocketManagerComponent::SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh,
    TSubclassOf<AStaticMeshActor> StaticMeshActorClass)
{
    // 입력 유효성 검사
    if (StaticMesh == nullptr || !DoesSocketExist(SocketTag)) return;

    // 스태틱 메시 액터 스폰
    auto SpawnedActor = SpawnStaticMeshActor(StaticMesh, StaticMeshActorClass);
    SpawnedActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
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
    ActorSpawnParameters.Name = FName(Owner->GetName() + "_" + ActorClass->GetName());
    ActorSpawnParameters.Owner = Owner;
    ActorSpawnParameters.Instigator = Owner->GetInstigator();
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 액터 스폰
    const FVector SpawnLocation = Owner->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);

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

    return SpawnedActor;
}

ASkeletalMeshActor* USocketManagerComponent::SpawnSkeletalMeshActor(USkeletalMesh* SkeletalMesh, TSubclassOf<ASkeletalMeshActor> SkeletalMeshActorClass)
{
    // 입력 유효성 검사
    if (SkeletalMesh == nullptr) return nullptr;

    // SkeletalMeshActorClass 설정
    if (SkeletalMeshActorClass == nullptr) SkeletalMeshActorClass = ASkeletalMeshActor::StaticClass();

    // 스켈레탈 메시 액터 스폰
    auto SpawnedActor = SpawnActorDeferred<ASkeletalMeshActor>(SkeletalMeshActorClass);
    if (SpawnedActor == nullptr) return nullptr;

    // 스켈레탈 메시 컴포넌트 설정
    auto SkeletalMeshComponent = SpawnedActor->GetSkeletalMeshComponent();
    SetBodyInstance(SkeletalMeshComponent);
    SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

    // 리플리케이트 설정
    SpawnedActor->SetReplicates(true);
    SkeletalMeshComponent->SetIsReplicated(true);
    SpawnedActor->FinishSpawning(FTransform(GetOwner()->GetActorLocation()));

    return SpawnedActor;
}

AStaticMeshActor* USocketManagerComponent::SpawnStaticMeshActor(UStaticMesh* StaticMesh, TSubclassOf<AStaticMeshActor> StaticMeshActorClass)
{
    // 입력 유효성 검사
    if (StaticMesh == nullptr) return nullptr;

    // StaticMeshActorClass 설정
    if (StaticMeshActorClass == nullptr) StaticMeshActorClass = AStaticMeshActor::StaticClass();

    // 스태틱 메시 액터 스폰
    auto SpawnedActor = SpawnActorDeferred<AStaticMeshActor>(StaticMeshActorClass);
    if (SpawnedActor == nullptr) return nullptr;

    // 스태틱 메시 컴포넌트 설정
    auto StaticMeshComponent = SpawnedActor->GetStaticMeshComponent();
    StaticMeshComponent->SetMobility(EComponentMobility::Movable);
    SetBodyInstance(StaticMeshComponent);
    StaticMeshComponent->SetStaticMesh(StaticMesh);

    // 리플리케이트 설정
    SpawnedActor->SetReplicates(true);
    StaticMeshComponent->SetIsReplicated(true);
    SpawnedActor->FinishSpawning(FTransform(GetOwner()->GetActorLocation()));

    return SpawnedActor;
}

void USocketManagerComponent::SetBodyInstance(UPrimitiveComponent* PrimitiveComponent)
{
    if (PrimitiveComponent == nullptr) return;

    if (OverrideBodyInstance.GetCollisionProfileName() == UCollisionProfile::CustomCollisionProfileName)
    {
        PrimitiveComponent->SetCollisionEnabled(OverrideBodyInstance.GetCollisionEnabled());
        PrimitiveComponent->SetCollisionObjectType(OverrideBodyInstance.GetObjectType());
        PrimitiveComponent->SetCollisionResponseToChannels(OverrideBodyInstance.GetResponseToChannels());
    }
    else
    {
        PrimitiveComponent->SetCollisionProfileName(OverrideBodyInstance.GetCollisionProfileName());
    }
}

bool USocketManagerComponent::DoesSocketExist(const FGameplayTag& SocketTag) const
{
    FName SocketName = GetSocketName(SocketTag);
    if (SocketName.IsNone()) return false;

    return TargetMesh.IsValid() && TargetMesh->DoesSocketExist(SocketName);
}
