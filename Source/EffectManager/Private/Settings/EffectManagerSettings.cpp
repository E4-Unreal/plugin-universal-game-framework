// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/EffectManagerSettings.h"

UEffectManagerSettings::UEffectManagerSettings()
{
    CategoryName = "Plugins";
    SectionName = "FootstepManager";
}

USoundBase* UEffectManagerSettings::GetSoundByPhysicalMaterial(UPhysicalMaterial* InPhysicalMaterial) const
{
    if (InPhysicalMaterial)
    {
        if (PhysicalMaterialSoundMap.Contains(InPhysicalMaterial))
        {
            return PhysicalMaterialSoundMap[InPhysicalMaterial].LoadSynchronous();
        }
        else
        {
            return GetSoundByPhysicalSurface(InPhysicalMaterial->SurfaceType);
        }
    }

    return nullptr;
}

USoundBase* UEffectManagerSettings::GetSoundByPhysicalSurface(EPhysicalSurface InPhysicalSurface) const
{
    return PhysicalSurfaceSoundMap.Contains(InPhysicalSurface) ? PhysicalSurfaceSoundMap[InPhysicalSurface].LoadSynchronous() : nullptr;
}
