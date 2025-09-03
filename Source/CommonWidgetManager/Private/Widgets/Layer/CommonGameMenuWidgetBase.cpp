// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonGameMenuWidgetBase.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

UCommonGameMenuWidgetBase::UCommonGameMenuWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = CommonWidgetManager::UI::Layer::Game::Menu;
}
