// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractableInterface.h"


// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

UActorComponent* IInteractableInterface::GetComponent() const
{
    if (auto Actor = Cast<AActor>(this))
    {
        return Actor->FindComponentByInterface(UInteractableInterface::StaticClass());
    }

    return nullptr;
}

FGameplayTag IInteractableInterface::GetInteractionType_Implementation() const
{
    if (auto Component = GetComponent())
    {
        return Execute_GetInteractionType(Component);
    }

    return FGameplayTag::EmptyTag;
}

FText IInteractableInterface::GetInteractionMessage_Implementation() const
{
    if (auto Component = GetComponent())
    {
        return Execute_GetInteractionMessage(Component);
    }

    return FText::GetEmpty();
}

float IInteractableInterface::GetInteractionDuration_Implementation() const
{
    if (auto Component = GetComponent())
    {
        return Execute_GetInteractionDuration(Component);
    }

    return 0.0f;
}

AActor* IInteractableInterface::GetInteractor_Implementation() const
{
    if (auto Component = GetComponent())
    {
        return Execute_GetInteractor(Component);
    }

    return nullptr;
}

bool IInteractableInterface::CanInteract_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        return Execute_CanInteract(Component, Interactor);
    }

    return false;
}

void IInteractableInterface::StartInteract_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        Execute_StartInteract(Component, Interactor);
    }
}

void IInteractableInterface::Interact_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        Execute_Interact(Component, Interactor);
    }
}

void IInteractableInterface::CancelInteract_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        Execute_CancelInteract(Component, Interactor);
    }
}

bool IInteractableInterface::CanSelect_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        return Execute_CanSelect(Component, Interactor);
    }

    return false;
}

void IInteractableInterface::Select_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        Execute_Select(Component, Interactor);
    }
}

void IInteractableInterface::Deselect_Implementation(AActor* Interactor)
{
    if (auto Component = GetComponent())
    {
        Execute_Deselect(Component, Interactor);
    }
}

