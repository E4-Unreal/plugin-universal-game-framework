// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PopupWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnWidgetHidden);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPopupWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IPopupWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTitleText(const FText& NewTitleText);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMessageText(const FText& NewMessageText);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindOnWidgetHidden(const FOnWidgetHidden& NewDelegate);
};
