// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSystemComponentBase.h"

#include "Interfaces/InteractableInterface.h"

void UInteractionSystemComponentBase::AddTarget(const TScriptInterface<IInteractableInterface>& NewTarget)
{
    AvailableTargets.AddUnique(NewTarget);

    RefreshTarget();
}

void UInteractionSystemComponentBase::RemoveTarget(const TScriptInterface<IInteractableInterface>& OldTarget)
{
    AvailableTargets.RemoveSingleSwap(OldTarget);

    RefreshTarget();
}

void UInteractionSystemComponentBase::TryInteract()
{
    if (CurrentTarget)
    {
        IInteractableInterface::Execute_TryInteract(CurrentTarget.GetObject(), GetOwner());
    }
}

void UInteractionSystemComponentBase::CancelInteract()
{
    if (CurrentTarget)
    {
        IInteractableInterface::Execute_TryInteract(CurrentTarget.GetObject(), GetOwner());
    }
}

void UInteractionSystemComponentBase::RefreshTarget()
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

float UInteractionSystemComponentBase::CalculateTargetDistance(const TScriptInterface<IInteractableInterface>& Target) const
{
    if (AActor* TargetActor = Cast<AActor>(Target.GetObject()))
    {
        FVector OwnerLocation = GetOwner()->GetActorLocation();
        FVector TargetLocation = TargetActor->GetActorLocation();

        return FVector::Dist(OwnerLocation, TargetLocation);
    }

    return MAX_flt;
}
