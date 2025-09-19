// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "InputActionConfigData.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct INPUTMANAGER_API FInputActionConfigData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputAction> InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSet<ETriggerEvent> TriggerEvents;
};
