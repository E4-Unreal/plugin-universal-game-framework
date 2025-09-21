// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonSystemMenuWidgetBase.h"

#include "GameplayTags/WidgetManagerGameplayTags.h"

UCommonSystemMenuWidgetBase::UCommonSystemMenuWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = WidgetManager::UI::Layer::System::Menu;

    UIInputConfig = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock);
    UIInputConfig.bIgnoreLookInput = true;
    UIInputConfig.bIgnoreMoveInput = true;
}
