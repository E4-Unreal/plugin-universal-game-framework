// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopupWidgetInterface.h"
#include "PromptWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPromptSubmitted, const FText&, SubmittedText);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPromptWidgetInterface : public UPopupWidgetInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IPromptWidgetInterface : public IPopupWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindOnPromptSubmitted(const FOnPromptSubmitted& NewDelegate);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetIsNumeric(bool bNewIsNumeric);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMinValue(float NewMinValue);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMaxValue(float NewMaxValue);
};
