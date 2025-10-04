// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class UInteractableInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class INTERACTIONSYSTEM_API IInteractableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetInteractionType() const;
    virtual FGameplayTag GetInteractionType_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FText GetInteractionMessage() const;
    virtual FText GetInteractionMessage_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetInteractionDuration() const;
    virtual float GetInteractionDuration_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    AActor* GetInteractor() const;
    virtual AActor* GetInteractor_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool CanInteract(AActor* Interactor);
    virtual bool CanInteract_Implementation(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void StartInteract(AActor* Interact);
    virtual void StartInteract_Implementation(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Interact(AActor* Interactor);
    virtual void Interact_Implementation(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void CancelInteract(AActor* Interactor);
    virtual void CancelInteract_Implementation(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool CanSelect(AActor* Interactor);
    virtual bool CanSelect_Implementation(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Select(AActor* Interactor);
    virtual void Select_Implementation(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Deselect(AActor* Interactor);
    virtual void Deselect_Implementation(AActor* Interactor);

private:
    virtual UActorComponent* GetComponent() const;
};
