// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSystemComponent.h"

#include "Interfaces/InteractableInterface.h"

UInteractionSystemComponent::UInteractionSystemComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;
}

void UInteractionSystemComponent::InitializeComponent()
{
    Super::InitializeComponent();

    if (!OverlapSphere.IsValid())
    {
        OverlapSphere = GetOwner()->GetComponentByClass<USphereComponent>();
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
}

void UInteractionSystemComponent::AddTarget(const TScriptInterface<IInteractableInterface>& NewTarget)
{
    if (!NewTarget.GetInterface()) return;

    AvailableTargets.AddUnique(NewTarget);

    RefreshTarget();
}

void UInteractionSystemComponent::RemoveTarget(const TScriptInterface<IInteractableInterface>& OldTarget)
{
    if (!OldTarget.GetInterface()) return;

    AvailableTargets.RemoveSingleSwap(OldTarget);

    RefreshTarget();
}

void UInteractionSystemComponent::TryInteract()
{
    if (CurrentTarget && IInteractableInterface::Execute_CanInteract(CurrentTarget.GetObject(), GetOwner()))
    {
        IInteractableInterface::Execute_Interact(CurrentTarget.GetObject(), GetOwner());
    }
}

void UInteractionSystemComponent::CancelInteract()
{
    if (CurrentTarget)
    {
        IInteractableInterface::Execute_CancelInteract(CurrentTarget.GetObject(), GetOwner());
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

void UInteractionSystemComponent::RefreshTarget()
{
    if (AvailableTargets.IsEmpty())
    {
        CurrentTarget = nullptr;
        return;
    }

    float MinDistance = MAX_flt;
    int32 MinIndex = 0;

    for (int32 Index = 0; Index < AvailableTargets.Num(); ++Index)
    {
        const auto& Target = AvailableTargets[Index];
        float Distance = CalculateTargetDistance(Target);
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            MinIndex = Index;
        }
    }

    CurrentTarget = AvailableTargets[MinIndex];
}

float UInteractionSystemComponent::CalculateTargetDistance(const TScriptInterface<IInteractableInterface>& Target) const
{
    if (AActor* TargetActor = Cast<AActor>(Target.GetObject()))
    {
        FVector OwnerLocation = GetOwner()->GetActorLocation();
        FVector TargetLocation = TargetActor->GetActorLocation();

        return FVector::Dist(OwnerLocation, TargetLocation);
    }

    return MAX_flt;
}
