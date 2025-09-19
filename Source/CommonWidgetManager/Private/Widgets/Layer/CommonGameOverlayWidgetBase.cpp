// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonGameOverlayWidgetBase.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

UCommonGameOverlayWidgetBase::UCommonGameOverlayWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bIsBackHandler = false;
    bIsModal = false;
    LayerTag = WidgetManager::UI::Layer::Game::Overlay;
}
