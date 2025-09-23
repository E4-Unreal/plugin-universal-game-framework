// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InteractionSystemSettings.generated.h"

/**
 *
 */
UCLASS(config = UniversalGameFramework, meta = (DisplayName = "InteractionSystem", ToolTip = "Settings for InteractionSystem"))
class INTERACTIONSYSTEM_API UInteractionSystemSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly, meta = (MustImplement = "InteractionWidgetInterface"))
    TSoftClassPtr<UUserWidget> DefaultInteractionWidgetClass;

public:
    UInteractionSystemSettings();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetInteractionSystemSettings"))
    static UInteractionSystemSettings* Get() { return GetMutableDefault<UInteractionSystemSettings>(); }

    UFUNCTION(BlueprintPure)
    TSubclassOf<UUserWidget> GetDefaultInteractionWidgetClass() const { return DefaultInteractionWidgetClass.LoadSynchronous(); }
};
