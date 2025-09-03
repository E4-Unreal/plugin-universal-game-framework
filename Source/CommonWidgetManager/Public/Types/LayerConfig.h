// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TransitionConfig.h"
#include "LayerConfig.generated.h"

USTRUCT(BlueprintType)
struct COMMONWIDGETMANAGER_API FLayerConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOverlay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransitionConfig TransitionConfig;
};
