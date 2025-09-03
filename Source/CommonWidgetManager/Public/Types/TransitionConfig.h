// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slate/SCommonAnimatedSwitcher.h"
#include "TransitionConfig.generated.h"

USTRUCT(BlueprintType)
struct COMMONWIDGETMANAGER_API FTransitionConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECommonSwitcherTransition TransitionType = ECommonSwitcherTransition::FadeOnly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETransitionCurve TransitionCurveType = ETransitionCurve::Linear;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TransitionDuration = 0.4f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECommonSwitcherTransitionFallbackStrategy TransitionFallbackStrategy = ECommonSwitcherTransitionFallbackStrategy::None;
};
