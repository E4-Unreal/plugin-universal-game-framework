// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableActorBase.generated.h"

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableActorBase : public AActor, public IInteractableInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    FGameplayTag InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText InteractionText;

public:
    AInteractableActorBase(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual FGameplayTag GetInteractionType_Implementation() const override { return InteractionType; }
    virtual FText GetInteractionText_Implementation() const override { return InteractionText; }
    virtual bool CanInteract_Implementation(AActor* Interactor) override { return true; }
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void CancelInteract_Implementation(AActor* Interactor) override;
    virtual void SetFocus_Implementation(AActor* Interactor) override;
    virtual void ClearFocus_Implementation(AActor* Interactor) override;
};
