// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonPopupWidgetBase.h"

#include "CommonTextBlock.h"
#include "GameplayTags/WidgetManagerGameplayTags.h"

UCommonPopupWidgetBase::UCommonPopupWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    LayerTag = WidgetManager::UI::Layer::System::Popup;

    UIInputConfig = FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock);
    UIInputConfig.bIgnoreLookInput = true;
    UIInputConfig.bIgnoreMoveInput = true;
}

void UCommonPopupWidgetBase::SetTitleText_Implementation(const FText& TitleText)
{
    if (GetTitleTextBlock())
    {
        GetTitleTextBlock()->SetText(TitleText);
    }
}

void UCommonPopupWidgetBase::SetMessageText_Implementation(const FText& MessageText)
{
    if (GetMessageTextBlock())
    {
        GetMessageTextBlock()->SetText(MessageText);
    }
}
