// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LayoutWidgetInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class ULayoutWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API ILayoutWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UUserWidget* ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void ExecuteBackAction();
};
