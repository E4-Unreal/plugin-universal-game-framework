// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSystemComponent.h"

#include "Interfaces/InteractableInterface.h"

UInteractionSystemComponent::UInteractionSystemComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    Range = 128.0f;
}

void UInteractionSystemComponent::InitializeComponent()
{
    Super::InitializeComponent();

    if (!OverlapSphere.IsValid())
    {
        SetOverlapSphere(GetOwner()->GetComponentByClass<USphereComponent>());
    }
}

void UInteractionSystemComponent::BeginPlay()
{
    Super::BeginPlay();

    if (OverlapSphere.IsValid())
    {
        OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
        OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereEndOverlap);
    }
}

void UInteractionSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    Super::OnComponentDestroyed(bDestroyingHierarchy);

    if (OverlapSphere.IsValid())
    {
        OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
        OverlapSphere->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnOverlapSphereEndOverlap);
    }
}

void UInteractionSystemComponent::SetOverlapSphere(USphereComponent* NewOverlapSphere)
{
    OverlapSphere = NewOverlapSphere;

    if (OverlapSphere.IsValid())
    {
        OverlapSphere->SetSphereRadius(Range);
    }
}

void UInteractionSystemComponent::AddTarget(AActor* NewTarget)
{
    if (NewTarget && NewTarget->Implements<UInteractableInterface>() && !AvailableTargets.Contains(NewTarget))
    {
        AvailableTargets.Emplace(NewTarget);

        SelectTargets();
    }
}

void UInteractionSystemComponent::RemoveTarget(AActor* OldTarget)
{
    if (OldTarget && AvailableTargets.Contains(OldTarget))
    {
        AvailableTargets.RemoveSingleSwap(OldTarget);

        SelectTargets();
    }
}

void UInteractionSystemComponent::SelectTarget(AActor* NewTarget, bool bForce)
{
    if (NewTarget && AvailableTargets.Contains(NewTarget) && !SelectedTargets.Contains(NewTarget))
    {
        if (bForce)
        {
            for (const auto& SelectedTarget : SelectedTargets)
            {
                DeselectTarget(SelectedTarget.Get());
            }
        }

        SelectedTargets.Emplace(NewTarget);

        IInteractableInterface::Execute_SetFocus(NewTarget, GetOwner());
    }
}

void UInteractionSystemComponent::DeselectTarget(AActor* OldTarget)
{
    if (OldTarget && SelectedTargets.Contains(OldTarget))
    {
        SelectedTargets.RemoveSingleSwap(OldTarget);

        IInteractableInterface::Execute_ClearFocus(OldTarget, GetOwner());
    }
}

void UInteractionSystemComponent::SetRange(float NewRange)
{
    Range = NewRange;

    if (OverlapSphere.IsValid())
    {
        OverlapSphere->SetSphereRadius(Range);
    }
}

bool UInteractionSystemComponent::TryInteract()
{
    if (SelectedTargets.IsEmpty()) return false;

    bool bResult = true;

    for (const auto& SelectedTarget : SelectedTargets)
    {
        if (SelectedTarget.IsValid() && IInteractableInterface::Execute_CanInteract(SelectedTarget.Get(), GetOwner()))
        {
            IInteractableInterface::Execute_Interact(SelectedTarget.Get(), GetOwner());
        }
        else
        {
            bResult = false;
        }
    }

    return bResult;
}

void UInteractionSystemComponent::CancelInteract()
{
    if (SelectedTargets.IsEmpty()) return;

    for (const auto& SelectedTarget : SelectedTargets)
    {
        if (SelectedTarget.IsValid())
        {
            IInteractableInterface::Execute_CancelInteract(SelectedTarget.Get(), GetOwner());
        }
    }
}

void UInteractionSystemComponent::OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    AddTarget(OtherActor);
}

void UInteractionSystemComponent::OnOverlapSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    RemoveTarget(OtherActor);
}

void UInteractionSystemComponent::SelectTargets()
{
    // 초기화
    for (const auto& SelectedTarget : SelectedTargets)
    {
        DeselectTarget(SelectedTarget.Get());
    }
    SelectedTargets.Reset();

    // 유효성 검사
    if (AvailableTargets.IsEmpty()) return;

    // 가장 가까운 액터 선택
    float MinDistance = MAX_flt;
    int32 MinIndex = 0;

    for (int32 Index = 0; Index < AvailableTargets.Num(); ++Index)
    {
        const auto& AvailableTarget = AvailableTargets[Index];
        if (!AvailableTarget.IsValid()) continue;

        float Distance = GetDistanceToTarget(AvailableTarget.Get());
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            MinIndex = Index;
        }
    }

    SelectTarget(AvailableTargets[MinIndex].Get());
}

float UInteractionSystemComponent::GetDistanceToTarget(AActor* Target) const
{
    if (Target)
    {
        FVector OwnerLocation = GetOwner()->GetActorLocation();
        FVector TargetLocation = Target->GetActorLocation();

        return FVector::Dist(OwnerLocation, TargetLocation);
    }

    return MAX_flt;
}
