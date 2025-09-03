// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LayerConfig.generated.h"

enum class ECommonSwitcherTransition : uint8;
enum class ETransitionCurve : uint8;
enum class ECommonSwitcherTransitionFallbackStrategy : uint8;

USTRUCT(BlueprintType)
struct COMMONWIDGETMANAGER_API FLayerConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOverlay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECommonSwitcherTransition TransitionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETransitionCurve TransitionCurveType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TransitionDuration = 0.4f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECommonSwitcherTransitionFallbackStrategy TransitionFallbackStrategy;
};
