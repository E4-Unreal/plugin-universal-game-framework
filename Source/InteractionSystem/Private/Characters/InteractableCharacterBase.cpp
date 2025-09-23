// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InteractableCharacterBase.h"

#include "Components/InteractableComponent.h"
#include "GameplayTags/InteractionGameplaytags.h"

FName AInteractableCharacterBase::InteractableComponentName(TEXT("InteractableComponent"));

AInteractableCharacterBase::AInteractableCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* InteractableComponent */

    InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(InteractableComponentName);
    GetInteractableComponent()->InteractionType = Interaction::Talk;
    GetInteractableComponent()->InteractionMessage = NSLOCTEXT("InteractionSystem", "Villager", "Villager");
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
    GetInteractableComponent()->Interact(Interactor);
}

void AInteractableCharacterBase::CancelInteract_Implementation(AActor* Interactor)
{
    GetInteractableComponent()->CancelInteract(Interactor);
}

bool AInteractableCharacterBase::CanSelect_Implementation(AActor* Interactor)
{
    return GetInteractableComponent()->CanSelect(Interactor);
}

void AInteractableCharacterBase::Select_Implementation(AActor* Interactor)
{
    GetInteractableComponent()->Select(Interactor);
}

void AInteractableCharacterBase::Deselect_Implementation(AActor* Interactor)
{
    GetInteractableComponent()->Deselect(Interactor);
}
