// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EffectManagerSettings.generated.h"

/**
 *
 */
UCLASS(config = UniversalGameFramework, meta = (DisplayName = "EffectManager", ToolTip = "Settings for EffectManager"))
class EFFECTMANAGER_API UEffectManagerSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly)
    TMap<TSoftObjectPtr<UPhysicalMaterial>, TSoftObjectPtr<USoundBase>> PhysicalMaterialSoundMap;

    UPROPERTY(Config, EditDefaultsOnly)
    TMap<TEnumAsByte<EPhysicalSurface>, TSoftObjectPtr<USoundBase>> PhysicalSurfaceSoundMap;

public:
    UEffectManagerSettings();

    /* API */

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetEffectManagerSettings"))
    static UEffectManagerSettings* Get() { return GetMutableDefault<UEffectManagerSettings>(); }

    UFUNCTION(BlueprintPure)
    USoundBase* GetSoundByPhysicalMaterial(UPhysicalMaterial* InPhysicalMaterial) const;

    UFUNCTION(BlueprintPure)
    USoundBase* GetSoundByPhysicalSurface(EPhysicalSurface InPhysicalSurface) const;
};
