// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayoutWidget.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

UCommonLayoutWidget::UCommonLayoutWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerConfig.Emplace(CommonWidgetManager::UI::Layer::Game::Overlay, true);
    LayerConfig.Emplace(CommonWidgetManager::UI::Layer::Game::Menu, true);
    LayerConfig.Emplace(CommonWidgetManager::UI::Layer::System::Menu, false);
    LayerConfig.Emplace(CommonWidgetManager::UI::Layer::System::Popup, false);
}
