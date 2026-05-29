// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/WidgetManagerSettings.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

UWidgetManagerSettings::UWidgetManagerSettings()
{
    CategoryName = "UniversalGameFramework";
    SectionName = "WidgetManager";

    LayerTags.Emplace(WidgetManager::UI::Layer::Game::Overlay);
    LayerTags.Emplace(WidgetManager::UI::Layer::Game::Menu);
    LayerTags.Emplace(WidgetManager::UI::Layer::System::Menu);
    LayerTags.Emplace(WidgetManager::UI::Layer::System::Popup);
}
