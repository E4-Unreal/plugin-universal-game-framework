// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "Engine/DataAsset.h"
#include "HitEffectDefinition.generated.h"

/**
 *
 */
UCLASS()
class EFFECTMANAGER_API UHitEffectDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<TEnumAsByte<EPhysicalSurface>, FGameplayCueTag> PhysicalSurfaceMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<TSoftObjectPtr<UPhysicalMaterial>, FGameplayCueTag> PhysicalMaterialMap;

public:
    UFUNCTION(BlueprintPure)
    FGameplayTag GetGameplayCueTagByPhysicalSurface(EPhysicalSurface PhysicalSurface) const;

    UFUNCTION(BlueprintPure)
    FGameplayTag GetGameplayCueTagByPhysicalMaterial(UPhysicalMaterial* PhysicalMaterial) const;
};
