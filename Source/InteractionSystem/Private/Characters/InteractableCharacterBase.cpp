// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InteractableCharacterBase.h"

#include "GameplayTags/InteractionGameplaytags.h"
#include "Logging.h"

AInteractableCharacterBase::AInteractableCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

FGameplayTag AInteractableCharacterBase::GetInteractionType_Implementation() const
{
    return Interaction::Talk;
}

FText AInteractableCharacterBase::GetInteractionMessage_Implementation() const
{
    return FText::GetEmpty();
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
    }
}

void AInteractableCharacterBase::ClearFocus_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}
