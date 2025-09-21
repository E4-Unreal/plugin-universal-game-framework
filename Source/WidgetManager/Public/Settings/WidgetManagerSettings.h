// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WidgetManagerSettings.generated.h"

/**
 *
 */
UCLASS(config = UniversalGameFramework, meta = (DisplayName = "WidgetManager", ToolTip = "Settings for WidgetManager"))
class WIDGETMANAGER_API UWidgetManagerSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly, meta = (MustImplement = "AlertWidgetInterface"))
    TSoftClassPtr<UUserWidget> DefaultAlertWidgetClass;

    UPROPERTY(Config, EditDefaultsOnly, meta = (MustImplement = "ConfirmWidgetInterface"))
    TSoftClassPtr<UUserWidget> DefaultConfirmWidgetClass;

    UPROPERTY(Config, EditDefaultsOnly, meta = (MustImplement = "PromptWidgetInterface"))
    TSoftClassPtr<UUserWidget> DefaultPromptWidgetClass;

public:
    UWidgetManagerSettings();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetWidgetManagerSettings"))
    static UWidgetManagerSettings* Get() { return GetMutableDefault<UWidgetManagerSettings>(); }

    UFUNCTION(BlueprintPure)
    TSubclassOf<UUserWidget> GetDefaultAlertWidgetClass() const { return DefaultAlertWidgetClass.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    TSubclassOf<UUserWidget> GetDefaultConfirmWidgetClass() const { return DefaultConfirmWidgetClass.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    TSubclassOf<UUserWidget> GetDefaultPromptWidgetClass() const { return DefaultPromptWidgetClass.LoadSynchronous(); }
};
