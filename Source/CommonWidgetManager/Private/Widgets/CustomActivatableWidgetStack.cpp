// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CustomActivatableWidgetStack.h"

void UCustomActivatableWidgetStack::SetTransitionConfig(const FTransitionConfig& TransitionConfig)
{
    TransitionType = TransitionConfig.TransitionType;
    TransitionCurveType = TransitionConfig.TransitionCurveType;
    TransitionDuration = TransitionConfig.TransitionDuration;
    TransitionFallbackStrategy = TransitionConfig.TransitionFallbackStrategy;
}
