// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"

#include "Logging.h"
#include "Components/InteractableComponent.h"

FName AInteractableActorBase::InteractableComponentName(TEXT("InteractableComponent"));

AInteractableActorBase::AInteractableActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* InteractableComponent */

    InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(InteractableComponentName);
}

FGameplayTag AInteractableActorBase::GetInteractionType_Implementation() const
{
    return InteractableComponent->InteractionType;
}

FText AInteractableActorBase::GetInteractionMessage_Implementation() const
{
    return InteractableComponent->InteractionMessage;
}

bool AInteractableActorBase::CanInteract_Implementation(AActor* Interactor)
{
    return InteractableComponent->CanInteract(Interactor);
}

void AInteractableActorBase::Interact_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}

void AInteractableActorBase::CancelInteract_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}

void AInteractableActorBase::SetFocus_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        if (GetInteractableComponent())
        {
            GetInteractableComponent()->ActivateFocusEffects(Interactor);
        }
    }
}

void AInteractableActorBase::ClearFocus_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        if (GetInteractableComponent())
        {
            GetInteractableComponent()->DeactivateFocusEffects(Interactor);
        }
    }
}
