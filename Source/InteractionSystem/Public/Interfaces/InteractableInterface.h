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

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FText GetInteractionText() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool CanInteract(AActor* Instigator);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Interact(AActor* Instigator);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void CancelInteract(AActor* Instigator);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnFocus(AActor* Instigator);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnUnFocus(AActor* Instigator);
};
