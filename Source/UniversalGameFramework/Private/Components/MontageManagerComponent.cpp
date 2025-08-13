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

    if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner()))
    {
        Mesh = OwningCharacter->GetMesh();
    }
    else
    {
        Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
    }
}

void UMontageManagerComponent::PlayMontage(UAnimMontage* Montage)
{
    if (Montage && Mesh.IsValid())
    {
        if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
        {
            AnimInstance->Montage_Play(Montage);
        }
    }
}
