// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TargetWidgetBase.h"

void UTargetWidgetBase::SetTargetActor_Implementation(AActor* NewTargetActor)
{
    if (TargetActor == NewTargetActor) return;

    TargetActor = NewTargetActor;

    if (TargetActor.IsValid())
    {
        TargetComponent = TargetActor->FindComponentByClass(TargetComponentClass);
    }
    else if (!FindComponentFromPlayer())
    {
        FindComponentFromPawn();
    }
}

bool UTargetWidgetBase::FindComponentFromPlayer()
{
    if (APlayerController* OwningPlayer = GetOwningPlayer())
    {
        TargetComponent =  OwningPlayer->FindComponentByClass(TargetComponentClass);
        if (TargetComponent.IsValid())
        {
            TargetActor = OwningPlayer;

            return true;
        }
    }

    return false;
}

bool UTargetWidgetBase::FindComponentFromPawn()
{
    if (APawn* OwningPawn = GetOwningPlayerPawn())
    {
        TargetComponent =  OwningPawn->FindComponentByClass(TargetComponentClass);
        if (TargetComponent.IsValid())
        {
            TargetActor = OwningPawn;

            return true;
        }
    }

    return false;
}
