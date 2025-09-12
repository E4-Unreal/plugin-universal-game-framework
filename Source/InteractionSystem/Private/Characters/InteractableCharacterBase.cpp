// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InteractableCharacterBase.h"

#include "Logging.h"
#include "Components/InteractableComponent.h"

FName AInteractableCharacterBase::InteractableComponentName(TEXT("InteractableComponent"));

AInteractableCharacterBase::AInteractableCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* InteractableComponent */

    InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(InteractableComponentName);
}

FGameplayTag AInteractableCharacterBase::GetInteractionType_Implementation() const
{
    return InteractableComponent->InteractionType;
}

FText AInteractableCharacterBase::GetInteractionMessage_Implementation() const
{
    return InteractableComponent->InteractionMessage;
}

bool AInteractableCharacterBase::CanInteract_Implementation(AActor* Interactor)
{
    return InteractableComponent->CanInteract(Interactor);
}

void AInteractableCharacterBase::Interact_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}

void AInteractableCharacterBase::CancelInteract_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}

void AInteractableCharacterBase::SetFocus_Implementation(AActor* Interactor)
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

void AInteractableCharacterBase::ClearFocus_Implementation(AActor* Interactor)
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
