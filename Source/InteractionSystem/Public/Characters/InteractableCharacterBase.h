// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableCharacterBase.generated.h"

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableCharacterBase : public ACharacter, public IInteractableInterface
{
    GENERATED_BODY()

public:
    AInteractableCharacterBase(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual FGameplayTag GetInteractionType_Implementation() const override;
    virtual FText GetInteractionMessage_Implementation() const override;
    virtual bool CanInteract_Implementation(AActor* Interactor) override { return true; }
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void CancelInteract_Implementation(AActor* Interactor) override;
    virtual void SetFocus_Implementation(AActor* Interactor) override;
    virtual void ClearFocus_Implementation(AActor* Interactor) override;
};
