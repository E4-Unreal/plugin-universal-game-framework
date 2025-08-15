// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSystemComponent.h"

#include "Interfaces/InteractableInterface.h"

void UInteractionSystemComponent::AddTarget(const TScriptInterface<IInteractableInterface>& NewTarget)
{
    AvailableTargets.AddUnique(NewTarget);

    RefreshTarget();
}

void UInteractionSystemComponent::RemoveTarget(const TScriptInterface<IInteractableInterface>& OldTarget)
{
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
