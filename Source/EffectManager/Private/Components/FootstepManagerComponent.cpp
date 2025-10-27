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
    GameplayCueParameters.EffectContext.AddHitResult(HitResult);
    GameplayCueParameters.EffectContext.AddInstigator(GetOwner(), GetOwner());

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(HitResult.GetActor(), GameplayCueTag, EGameplayCueEvent::Executed, GameplayCueParameters);
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

UHitEffectDefinition* UFootstepManagerComponent::GetHitEffectDefinition() const
{
    return HitEffectDefinition ? HitEffectDefinition.Get() : UEffectManagerSettings::Get()->GetFootstepEffectDefinition();
}
