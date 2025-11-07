// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/HitEffectDefinition.h"

FGameplayTag UHitEffectDefinition::GetGameplayCueTagByPhysicalSurface(EPhysicalSurface PhysicalSurface) const
{
    return PhysicalSurfaceMap.FindRef(PhysicalSurface).GameplayCueTag;
}

FGameplayTag UHitEffectDefinition::GetGameplayCueTagByPhysicalMaterial(UPhysicalMaterial* PhysicalMaterial) const
{
    FGameplayTag GameplayCueTag;

    if (PhysicalMaterial)
    {
        if (PhysicalMaterialMap.Contains(PhysicalMaterial))
        {
            GameplayCueTag = PhysicalMaterialMap[PhysicalMaterial].GameplayCueTag;
        }
        else
        {
            GameplayCueTag = GetGameplayCueTagByPhysicalSurface(PhysicalMaterial->SurfaceType);
        }
    }

    return GameplayCueTag;
}
