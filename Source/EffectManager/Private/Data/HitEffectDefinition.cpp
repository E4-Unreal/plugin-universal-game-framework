// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/HitEffectDefinition.h"

FGameplayCueTag UHitEffectDefinition::GetGameplayCueTagByPhysicalSurface(EPhysicalSurface PhysicalSurface) const
{
    return PhysicalSurfaceMap.FindRef(PhysicalSurface);
}

FGameplayCueTag UHitEffectDefinition::GetGameplayCueTagByPhysicalMaterial(UPhysicalMaterial* PhysicalMaterial) const
{
    if (PhysicalMaterial)
    {
        if (PhysicalMaterialMap.Contains(PhysicalMaterial))
        {
            return PhysicalMaterialMap[PhysicalMaterial];
        }
        else
        {
            return GetGameplayCueTagByPhysicalSurface(PhysicalMaterial->SurfaceType);
        }
    }

    return FGameplayCueTag(FGameplayTag::EmptyTag);
}
