// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionWidgetComponent.h"


UInteractionWidgetComponent::UInteractionWidgetComponent()
{
    SetVisibility(false);
    SetWidgetSpace(EWidgetSpace::Screen);
    SetDrawAtDesiredSize(true);
}
