﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
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

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool CanInteract(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void TryInteract(AActor* Interactor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void CancelInteract(AActor* Interactor);
};
