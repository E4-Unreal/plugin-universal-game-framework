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
    return GetInteractableComponent()->InteractionType;
}

FText AInteractableActorBase::GetInteractionMessage_Implementation() const
{
    return GetInteractableComponent()->InteractionMessage;
}

bool AInteractableActorBase::CanInteract_Implementation(AActor* Interactor)
{
    return GetInteractableComponent()->CanInteract(Interactor);
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

bool AInteractableActorBase::CanSelect_Implementation(AActor* Interactor)
{
    return GetInteractableComponent()->CanSelect(Interactor);
}

void AInteractableActorBase::Select_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        GetInteractableComponent()->ActivateFocusEffects(Interactor);
    }
}

void AInteractableActorBase::Deselect_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        GetInteractableComponent()->DeactivateFocusEffects(Interactor);
    }
}
