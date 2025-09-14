// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MontageManagerComponent.h"

#include "GameFramework/Character.h"


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
    if (SkeletalMesh == NewSkeletalMesh) return;

    SkeletalMesh = NewSkeletalMesh;
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

void UMontageManagerComponent::PlayMontage(UAnimMontage* Montage)
{
    if (Montage && SkeletalMesh.IsValid())
    {
        if (UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance())
        {
            AnimInstance->Montage_Play(Montage);
        }
    }
}

UAnimMontage* UMontageManagerComponent::GetMontageByTag(const FGameplayTag& Tag) const
{
    UAnimMontage* Montage = nullptr;
    FGameplayTagContainer TagContainer = Tag.GetGameplayTagParents();
    for (const FGameplayTag& ParentTag : TagContainer)
    {
        if (MontageMap.Contains(ParentTag))
        {
            Montage = MontageMap[ParentTag];
            break;
        }
    }

    return Montage;
}

void UMontageManagerComponent::PlayMontageByTag(const FGameplayTag& Tag)
{
    PlayMontage(GetMontageByTag(Tag));
}
