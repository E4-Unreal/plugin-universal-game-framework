// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Common/CommonLayoutWidget.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

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
    SetLayer(Widget::Layer::Game::Overlay, GetGameOverlayLayer());
    SetLayer(Widget::Layer::Game::Menu, GetGameMenuLayer());
    SetLayer(Widget::Layer::System::Popup, GetSystemPopupLayer());
    SetLayer(Widget::Layer::System::Menu, GetSystemMenuLayer());
}
