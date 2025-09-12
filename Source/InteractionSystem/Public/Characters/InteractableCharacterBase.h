// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableCharacterBase.generated.h"

class UInteractableComponent;

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableCharacterBase : public ACharacter, public IInteractableInterface
{
    GENERATED_BODY()

protected:
    static FName InteractableComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInteractableComponent> InteractableComponent;

public:
    AInteractableCharacterBase(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual FGameplayTag GetInteractionType_Implementation() const override;
    virtual FText GetInteractionMessage_Implementation() const override;
    virtual bool CanInteract_Implementation(AActor* Interactor) override;
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void CancelInteract_Implementation(AActor* Interactor) override;
    virtual bool CanSelect_Implementation(AActor* Interactor) override;
    virtual void Select_Implementation(AActor* Interactor) override;
    virtual void Deselect_Implementation(AActor* Interactor) override;

public:
    FORCEINLINE UInteractableComponent* GetInteractableComponent() const { return InteractableComponent; }
};
