// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FootstepManagerSettings.generated.h"

/**
 *
 */
UCLASS(config = UniversalGameFramework, meta = (DisplayName = "FootstepManager", ToolTip = "Settings for FootstepManager"))
class FOOTSTEPMANAGER_API UFootstepManagerSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly)
    TMap<TSoftObjectPtr<UPhysicalMaterial>, TSoftObjectPtr<USoundBase>> PhysicalMaterialSoundMap;

    UPROPERTY(Config, EditDefaultsOnly)
    TMap<TEnumAsByte<EPhysicalSurface>, TSoftObjectPtr<USoundBase>> PhysicalSurfaceSoundMap;

public:
    UFootstepManagerSettings();

    /* API */

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetFootstepManagerSettings"))
    static UFootstepManagerSettings* Get() { return GetMutableDefault<UFootstepManagerSettings>(); }

    UFUNCTION(BlueprintPure)
    USoundBase* GetSoundByPhysicalMaterial(UPhysicalMaterial* InPhysicalMaterial) const;

    UFUNCTION(BlueprintPure)
    USoundBase* GetSoundByPhysicalSurface(EPhysicalSurface InPhysicalSurface) const;
};
