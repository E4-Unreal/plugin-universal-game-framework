// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayoutWidget.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

void UCommonLayoutWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SetLayers();
}

void UCommonLayoutWidget::NativePreConstruct()
{
#if WITH_EDITOR
    SetLayers();
#endif

    Super::NativePreConstruct();
}

void UCommonLayoutWidget::SetLayers()
{
    SetLayer(CommonWidgetManager::UI::Layer::Game::Overlay, GetGameOverlayLayer());
    SetLayer(CommonWidgetManager::UI::Layer::Game::Menu, GetGameMenuLayer());
    SetLayer(CommonWidgetManager::UI::Layer::System::Popup, GetSystemPopupLayer());
    SetLayer(CommonWidgetManager::UI::Layer::System::Menu, GetSystemMenuLayer());
}
