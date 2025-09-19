// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayoutWidget.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

UCommonLayoutWidget::UCommonLayoutWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    FLayerConfig GameOverlayLayerConfig;
    GameOverlayLayerConfig.bIsOverlay = true;
    GameOverlayLayerConfig.TransitionConfig.TransitionDuration = 0.0f;

    FLayerConfig GameMenuLayerConfig;
    GameMenuLayerConfig.bIsOverlay = true;
    GameMenuLayerConfig.TransitionConfig.TransitionDuration = 0.0f;

    FLayerConfig SystemMenuLayerConfig;

    FLayerConfig SystemPopupLayerConfig;

    LayerConfigs.Emplace(WidgetManager::UI::Layer::Game::Overlay, GameOverlayLayerConfig);
    LayerConfigs.Emplace(WidgetManager::UI::Layer::Game::Menu, GameMenuLayerConfig);
    LayerConfigs.Emplace(WidgetManager::UI::Layer::System::Menu, SystemMenuLayerConfig);
    LayerConfigs.Emplace(WidgetManager::UI::Layer::System::Popup, SystemPopupLayerConfig);
}
