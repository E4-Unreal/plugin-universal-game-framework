// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"

#include "GameplayTags/InteractionGameplaytags.h"
#include "Logging.h"

AInteractableActorBase::AInteractableActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

FGameplayTag AInteractableActorBase::GetInteractionType_Implementation() const
{
    return Interaction::Root;
}

FText AInteractableActorBase::GetInteractionText_Implementation() const
{
    return NSLOCTEXT("InteractionSystem", "Interact", "Interact");
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
    }
}

void AInteractableActorBase::ClearFocus_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}
