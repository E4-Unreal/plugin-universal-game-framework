// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/FootstepManagerSettings.h"

UFootstepManagerSettings::UFootstepManagerSettings()
{
    CategoryName = "Plugins";
    SectionName = "FootstepManager";
}

USoundBase* UFootstepManagerSettings::GetSoundByPhysicalMaterial(UPhysicalMaterial* InPhysicalMaterial) const
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

USoundBase* UFootstepManagerSettings::GetSoundByPhysicalSurface(EPhysicalSurface InPhysicalSurface) const
{
    return PhysicalSurfaceSoundMap.Contains(InPhysicalSurface) ? PhysicalSurfaceSoundMap[InPhysicalSurface].LoadSynchronous() : nullptr;
}
