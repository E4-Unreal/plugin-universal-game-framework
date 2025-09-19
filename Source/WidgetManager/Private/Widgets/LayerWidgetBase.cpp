// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LayerWidgetBase.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

ULayerWidgetBase::ULayerWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = WidgetManager::UI::Layer::Game::Overlay;
}
