// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PromptWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPromptSubmitted, const FText&, SubmittedText);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPromptWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IPromptWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindOnPromptSubmitted(const FOnPromptSubmitted& NewDelegate);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetNumeric(bool bNewNumeric);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMinValue(float NewMinValue);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMaxValue(float NewMaxValue);
};
