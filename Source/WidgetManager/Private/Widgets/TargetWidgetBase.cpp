// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TargetWidgetBase.h"

void UTargetWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindComponent();
}

void UTargetWidgetBase::SetTargetActor_Implementation(AActor* NewTargetActor)
{
    if (NewTargetActor)
    {
        SetTargetComponent(NewTargetActor->FindComponentByClass(TargetComponentClass));
    }
}

void UTargetWidgetBase::SetTargetComponent_Implementation(UActorComponent* NewTargetComponent)
{
    auto OldTargetComponent = TargetComponent.Get();
    TargetComponent = NewTargetComponent;
    OnTargetComponentChanged(OldTargetComponent);
}

void UTargetWidgetBase::FindComponent()
{
    if (TargetComponent.IsValid()) return;

    if (APlayerController* OwningPlayer = GetOwningPlayer())
    {
        SetTargetComponent(OwningPlayer->FindComponentByClass(TargetComponentClass));
    }

    if (TargetComponent.IsValid()) return;

    if (APawn* OwningPawn = GetOwningPlayerPawn())
    {
        SetTargetComponent(OwningPawn->FindComponentByClass(TargetComponentClass));
    }
}

void UTargetWidgetBase::BindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent)
{
    // Bind Events
}

void UTargetWidgetBase::UnbindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent)
{
    // Unbind Events
}

void UTargetWidgetBase::OnTargetComponentChanged_Implementation(UActorComponent* OldTargetComponent)
{
    if (OldTargetComponent) UnbindTargetComponentEvents(OldTargetComponent);
    if (TargetComponent.IsValid()) BindTargetComponentEvents(TargetComponent.Get());
}
