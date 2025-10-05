// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetUtilityInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UWidgetUtilityInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IWidgetUtilityInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Refresh();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Clear();
};
