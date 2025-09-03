// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonGameOverlayWidgetBase.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

UCommonGameOverlayWidgetBase::UCommonGameOverlayWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = CommonWidgetManager::UI::Layer::Game::Overlay;
}
