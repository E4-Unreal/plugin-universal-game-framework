// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FootstepManagerComponent.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GameplayEffectTypes.h"
#include "Data/HitEffectDefinition.h"
#include "GameFramework/Character.h"
#include "Settings/EffectManagerSettings.h"


UFootstepManagerComponent::UFootstepManagerComponent()
{
    TraceChannel = ECC_Visibility;
    TraceDistance = 100.0f;
    SocketNameMap.Emplace(0, "root");
    SocketNameMap.Emplace(1, "foot_r");
    SocketNameMap.Emplace(2, "foot_l");
}

void UFootstepManagerComponent::OnRegister()
{
    Super::OnRegister();

    FindRootMesh();
}

void UFootstepManagerComponent::SetRootMesh(USkeletalMeshComponent* NewRootMesh)
{
    if (NewRootMesh == nullptr || RootMesh == NewRootMesh) return;

    RootMesh = NewRootMesh;
}

void UFootstepManagerComponent::SpawnEffect(FName SocketName)
{
    // 유효성 검사
    if (!RootMesh.IsValid() || !RootMesh->DoesSocketExist(SocketName)) return;

    auto World = GetWorld();
    if (World == nullptr) return;

    // 라인 트레이스
    FHitResult HitResult;
    FVector TraceStart = RootMesh->GetSocketLocation(SocketName);
    FVector TraceEnd = TraceStart - RootMesh->GetUpVector() * TraceDistance;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    CollisionQueryParams.bReturnPhysicalMaterial = true;

    World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, TraceChannel, CollisionQueryParams);

    if (!HitResult.bBlockingHit) return;

    // 게임플레이 큐 처리
    auto LocalHitEffectDefinition = GetHitEffectDefinition();
    if (LocalHitEffectDefinition == nullptr) return;

    auto GameplayCueTag = LocalHitEffectDefinition->GetGameplayCueTagByPhysicalMaterial(HitResult.PhysMaterial.Get());
    if (!GameplayCueTag.IsValid()) return;

    FGameplayCueParameters GameplayCueParameters;
    FGameplayEffectContextHandle GameplayEffectContextHandle = FGameplayEffectContextHandle(UAbilitySystemGlobals::Get().AllocGameplayEffectContext());
    GameplayEffectContextHandle.AddHitResult(HitResult);
    GameplayEffectContextHandle.AddInstigator(GetOwner(), GetOwner());
    GameplayCueParameters.EffectContext = GameplayEffectContextHandle;

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(HitResult.GetActor(), GameplayCueTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}

void UFootstepManagerComponent::SpawnEffectByIndex(int32 Index)
{
    const FName SocketName = GetSocketNameByIndex(Index);
    if (SocketName.IsNone()) return;

    SpawnEffect(SocketName);
}

void UFootstepManagerComponent::FindRootMesh()
{
    if (RootMesh.IsValid()) return;

    USkeletalMeshComponent* FoundRootMesh = nullptr;

    if (auto Character = Cast<ACharacter>(GetOwner()))
    {
        FoundRootMesh = Character->GetMesh();
    }
    else
    {
        FoundRootMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
    }

    SetRootMesh(FoundRootMesh);
}

FName UFootstepManagerComponent::GetSocketNameByIndex(int32 Index) const
{
    return SocketNameMap.FindRef(Index);
}

UHitEffectDefinition* UFootstepManagerComponent::GetHitEffectDefinition() const
{
    return HitEffectDefinition ? HitEffectDefinition.Get() : UEffectManagerSettings::Get()->GetFootstepEffectDefinition();
}
