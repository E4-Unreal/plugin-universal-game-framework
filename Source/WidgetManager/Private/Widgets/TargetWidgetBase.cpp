// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TargetWidgetBase.h"

void UTargetWidgetBase::SetTargetActor(AActor* NewTargetActor)
{
    if (TargetActor == NewTargetActor) return;

    TargetActor = NewTargetActor;
    TargetComponent = TargetActor.IsValid() && TargetComponentClass ? TargetActor->FindComponentByClass(TargetComponentClass) : nullptr;
}

void UTargetWidgetBase::SetTargetComponent(UActorComponent* NewTargetComponent)
{
    if (TargetComponent == NewTargetComponent) return;

    TargetComponent = NewTargetComponent;
    TargetActor = TargetComponent.IsValid() ? TargetComponent->GetOwner() : nullptr;
}
