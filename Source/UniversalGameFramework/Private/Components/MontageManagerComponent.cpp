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

    if (!Mesh.IsValid())
    {
        if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner()))
        {
            Mesh = OwningCharacter->GetMesh();
        }
        else
        {
            Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
        }
    }
}

void UMontageManagerComponent::SetMesh(USkeletalMeshComponent* NewMesh)
{
    Mesh = NewMesh;
}

void UMontageManagerComponent::PlayMontage(UAnimMontage* Montage) const
{
    if (Montage && Mesh.IsValid())
    {
        if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
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

void UMontageManagerComponent::PlayMontageByTag(const FGameplayTag& Tag) const
{
    PlayMontage(GetMontageByTag(Tag));
}
