// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonSystemMenuWidgetBase.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

UCommonSystemMenuWidgetBase::UCommonSystemMenuWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = CommonWidgetManager::UI::Layer::System::Menu;
}
