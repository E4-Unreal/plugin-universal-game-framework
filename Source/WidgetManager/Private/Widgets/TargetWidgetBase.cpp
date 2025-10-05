// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TargetWidgetBase.h"

void UTargetWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindComponent();
}

void UTargetWidgetBase::Refresh_Implementation()
{

}

void UTargetWidgetBase::Clear_Implementation()
{

}

void UTargetWidgetBase::SetTargetActor_Implementation(AActor* NewTargetActor)
{
    if (TargetActor == NewTargetActor) return;
    TargetActor = NewTargetActor;

    if (TargetActor.IsValid())
    {
        SetTargetComponent(TargetActor->FindComponentByClass(TargetComponentClass));
    }
}

void UTargetWidgetBase::SetTargetComponent_Implementation(UActorComponent* NewTargetComponent)
{
    if (TargetComponent == NewTargetComponent) return;
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
    if (OldTargetComponent)
    {
        UnbindTargetComponentEvents(OldTargetComponent);
        Clear();
    }

    if (TargetComponent.IsValid())
    {
        BindTargetComponentEvents(TargetComponent.Get());
        Refresh();
    }
}
