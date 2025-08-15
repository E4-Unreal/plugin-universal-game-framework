// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/ShapeComponent.h"
#include "Logging.h"

void UInteractableComponent::BeginPlay()
{
    Super::BeginPlay();

    // Find OverlapShape
    if (!GetOverlapShape()) SetOverlapShape(GetOwner()->FindComponentByClass<UShapeComponent>());

    // Bind Events
    if (GetOverlapShape())
    {
        GetOverlapShape()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeBeginOverlap);
        GetOverlapShape()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeEndOverlap);
    }
}

void UInteractableComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    ClearAllInteractionTimers();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UInteractableComponent::Interact_Implementation(AActor* Interactor)
{
    if (!Execute_CanInteract(this, Interactor)) return;

    LOG_ACTOR_COMPONENT(Log, TEXT("%s try interact."), *Interactor->GetName())
    SetInteractionTimer(Interactor);
}

void UInteractableComponent::CancelInteract_Implementation(AActor* Interactor)
{
    if (!IsInteracting(Interactor)) return;

    LOG_ACTOR_COMPONENT(Log, TEXT("%s cancel interact."), *Interactor->GetName())
    ClearInteractionTimer(Interactor);
}

void UInteractableComponent::SetInteractionTimer(AActor* Interactor)
{
    ClearInteractionTimer(Interactor);

    if (InteractionTime < 0 || FMath::IsNearlyZero(InteractionTime))
    {
        TriggerInteraction(Interactor);
    }
    else
    {
        FTimerHandle Timer;
        FTimerDelegate TimerDelegate;
        TimerDelegate.BindUObject(this, &ThisClass::TriggerInteraction, Interactor);
        GetOwner()->GetWorldTimerManager().SetTimer(Timer, TimerDelegate, InteractionTime, false);

        InteractionTimerMap.Emplace(Interactor, Timer);
    }
}

void UInteractableComponent::ClearInteractionTimer(AActor* Interactor)
{
    if (InteractionTimerMap.Contains(Interactor))
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(InteractionTimerMap[Interactor]);
        InteractionTimerMap.Remove(Interactor);
    }
}

void UInteractableComponent::ClearAllInteractionTimers()
{
    for (const auto& [Interactor, Timer] : InteractionTimerMap)
    {
        ClearInteractionTimer(Interactor);
    }
}

void UInteractableComponent::TriggerInteraction(AActor* Interactor)
{
    ClearInteractionTimer(Interactor);

    if (Execute_CanInteract(this, Interactor))
    {
        if (bCanInteractOnlyOnce)
        {
            bCanInteract = false;
            ClearAllInteractionTimers();
        }

        LOG_ACTOR_COMPONENT(Log, TEXT("%s trigger interaction."), *Interactor->GetName(), *GetOwner()->GetName())
        OnInteractionTriggered.Broadcast(Interactor);
    }
}

void UInteractableComponent::OnOverlapShapeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (auto InteractionSystem = OtherActor->GetComponentByClass<UInteractionSystemComponent>())
    {
        OnInteractorBeginOverlap(OtherActor, InteractionSystem);
    }
}

void UInteractableComponent::OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (auto InteractionSystem = OtherActor->GetComponentByClass<UInteractionSystemComponent>())
    {
        OnInteractorEndOverlap(OtherActor, InteractionSystem);
    }
}

void UInteractableComponent::OnInteractorBeginOverlap_Implementation(AActor* Interactor,
    UInteractionSystemComponent* InteractionSystem)
{
    InteractionSystem->AddTarget(this);
}

void UInteractableComponent::OnInteractorEndOverlap_Implementation(AActor* Interactor,
    UInteractionSystemComponent* InteractionSystem)
{
    InteractionSystem->RemoveTarget(this);
}
