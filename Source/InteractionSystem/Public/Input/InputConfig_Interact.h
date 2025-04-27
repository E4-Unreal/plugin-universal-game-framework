// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputConfig_PressAndRelease.h"
#include "InputConfig_Interact.generated.h"

class UInputAction;

/**
 *
 */
UCLASS()
class INTERACTIONSYSTEM_API UInputConfig_Interact : public UInputConfig_PressAndRelease
{
    GENERATED_BODY()

protected:
    virtual void OnStarted_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance) override;
    virtual void OnCompleted_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance) override;

    virtual void TryInteract(APawn* Pawn);

    virtual void CancelInteract(APawn* Pawn);
};
