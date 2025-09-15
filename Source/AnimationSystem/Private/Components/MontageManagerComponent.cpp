// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MontageManagerComponent.h"

#include "GameFramework/Character.h"
#include "Logging.h"
#include "Misc/MapErrors.h"

UMontageManagerComponent::UMontageManagerComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;
}

void UMontageManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindSkeletalMesh();
}

void UMontageManagerComponent::SetSkeletalMesh(USkeletalMeshComponent* NewSkeletalMesh)
{
    if (SkeletalMesh.IsValid() || NewSkeletalMesh == nullptr) return;
    SkeletalMesh = NewSkeletalMesh;

    BindAnimInstanceEvents();
    SkeletalMesh->OnAnimInitialized.AddDynamic(this, &ThisClass::BindAnimInstanceEvents);
}

void UMontageManagerComponent::FindSkeletalMesh()
{
    if (SkeletalMesh.IsValid()) return;

    if (ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetSkeletalMesh(OwnerCharacter->GetMesh());
    }
    else
    {
        SetSkeletalMesh(GetOwner()->GetComponentByClass<USkeletalMeshComponent>());
    }
}

bool UMontageManagerComponent::PlayMontage(UAnimMontage* Montage)
{
    if (Montage && SkeletalMesh.IsValid())
    {
        if (UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance())
        {
            AnimInstance->Montage_Play(Montage);

            return true;
        }
    }

    return false;
}

bool UMontageManagerComponent::PlayMontageByTag(const FGameplayTag& Tag)
{
    return PlayMontage(GetMontageByTag(Tag));
}


void UMontageManagerComponent::BindAnimInstanceEvents()
{
    if (SkeletalMesh.IsValid())
    {
        if (auto AnimInstance = SkeletalMesh->GetAnimInstance())
        {
            AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UMontageManagerComponent::OnPlayMontageNotifyBegin);
            AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UMontageManagerComponent::OnPlayMontageNotifyEnd);
        }
    }
}

void UMontageManagerComponent::OnPlayMontageNotifyBegin(FName NotifyName,
    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    LOG_ACTOR_COMPONENT(Log, TEXT("NotifyName: %s"), *NotifyName.ToString())
}

void UMontageManagerComponent::OnPlayMontageNotifyEnd(FName NotifyName,
    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    LOG_ACTOR_COMPONENT(Log, TEXT("NotifyName: %s"), *NotifyName.ToString())
}
