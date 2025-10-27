// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/EffectManagerSettings.h"

UEffectManagerSettings::UEffectManagerSettings()
{
    CategoryName = "Plugins";
    SectionName = "FootstepManager";
}

UHitEffectDefinition* UEffectManagerSettings::GetFootstepEffectDefinition() const
{
    return !FootstepEffectDefinition.IsNull() ? FootstepEffectDefinition.LoadSynchronous() : nullptr;
}
