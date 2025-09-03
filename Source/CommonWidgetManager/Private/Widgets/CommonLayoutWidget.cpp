// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayoutWidget.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

UCommonLayoutWidget::UCommonLayoutWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    FLayerConfig GameOverlayLayerConfig;
    GameOverlayLayerConfig.bIsOverlay = true;

    FLayerConfig GameMenuLayerConfig;
    GameMenuLayerConfig.bIsOverlay = true;
    GameMenuLayerConfig.TransitionConfig.TransitionDuration = 0.0f;

    FLayerConfig SystemMenuLayerConfig;

    FLayerConfig SystemPopupLayerConfig;

    LayerConfigs.Emplace(CommonWidgetManager::UI::Layer::Game::Overlay, GameOverlayLayerConfig);
    LayerConfigs.Emplace(CommonWidgetManager::UI::Layer::Game::Menu, GameMenuLayerConfig);
    LayerConfigs.Emplace(CommonWidgetManager::UI::Layer::System::Menu, SystemMenuLayerConfig);
    LayerConfigs.Emplace(CommonWidgetManager::UI::Layer::System::Popup, SystemPopupLayerConfig);
}
