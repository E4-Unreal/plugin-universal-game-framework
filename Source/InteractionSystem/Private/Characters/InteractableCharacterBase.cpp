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
    return GetInteractableComponent()->InteractionType;
}

FText AInteractableCharacterBase::GetInteractionMessage_Implementation() const
{
    return GetInteractableComponent()->InteractionMessage;
}

bool AInteractableCharacterBase::CanInteract_Implementation(AActor* Interactor)
{
    return GetInteractableComponent()->CanInteract(Interactor);
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

bool AInteractableCharacterBase::CanSelect_Implementation(AActor* Interactor)
{
    return GetInteractableComponent()->CanSelect(Interactor);
}

void AInteractableCharacterBase::Select_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        GetInteractableComponent()->Select(Interactor);
    }
}

void AInteractableCharacterBase::Deselect_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        GetInteractableComponent()->Deselect(Interactor);
    }
}
