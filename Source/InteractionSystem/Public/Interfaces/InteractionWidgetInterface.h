// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "InteractionWidgetInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UInteractionWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class INTERACTIONSYSTEM_API IInteractionWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetInteractionType(FGameplayTag NewInteractionType);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetInteractionMessage(const FText& NewInteractionMessage);
};
