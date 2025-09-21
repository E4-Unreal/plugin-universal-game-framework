// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonGameMenuWidgetBase.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

UCommonGameMenuWidgetBase::UCommonGameMenuWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = WidgetManager::UI::Layer::Game::Menu;
}
