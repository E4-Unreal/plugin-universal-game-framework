// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonSystemMenuWidgetBase.h"

#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

UCommonSystemMenuWidgetBase::UCommonSystemMenuWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = CommonWidgetManager::UI::Layer::System::Menu;

    UIInputConfig = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock);
    UIInputConfig.bIgnoreLookInput = true;
    UIInputConfig.bIgnoreMoveInput = true;
}
