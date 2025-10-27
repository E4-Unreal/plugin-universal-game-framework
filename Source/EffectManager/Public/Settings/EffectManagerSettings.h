// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EffectManagerSettings.generated.h"

class UHitEffectDefinition;

/**
 *
 */
UCLASS(config = UniversalGameFramework, meta = (DisplayName = "EffectManager", ToolTip = "Settings for EffectManager"))
class EFFECTMANAGER_API UEffectManagerSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly)
    TSoftObjectPtr<UHitEffectDefinition> FootstepEffectDefinition;

public:
    UEffectManagerSettings();

    /* API */

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetEffectManagerSettings"))
    static UEffectManagerSettings* Get() { return GetMutableDefault<UEffectManagerSettings>(); }

    UFUNCTION(BlueprintPure)
    UHitEffectDefinition* GetFootstepEffectDefinition() const;
};
