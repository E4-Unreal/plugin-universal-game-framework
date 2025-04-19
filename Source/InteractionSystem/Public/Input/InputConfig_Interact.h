// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputConfig.h"
#include "InputConfig_Interact.generated.h"

class UInputAction;

/**
 *
 */
UCLASS()
class INTERACTIONSYSTEM_API UInputConfig_Interact : public UInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UInputAction> InteractAction;

protected:
    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;

    virtual void TryInteract(APawn* Pawn);

    virtual void CancelInteract(APawn* Pawn);
};
