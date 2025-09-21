// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ConfirmWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnButtonClicked);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UConfirmWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IConfirmWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindOnConfirmButtonClicked(const FOnButtonClicked& NewDelegate);
};
