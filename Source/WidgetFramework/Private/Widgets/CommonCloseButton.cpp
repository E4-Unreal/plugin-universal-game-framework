// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonCloseButton.h"

#include "CommonUIUtils.h"

UCommonCloseButton::UCommonCloseButton(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ButtonText = FText::FromString(TEXT("X"));
}

void UCommonCloseButton::NativeOnClicked()
{
    Super::NativeOnClicked();

    UUserWidget* OwningUserWidget = CommonUIUtils::GetOwningUserWidget(this);
    OwningUserWidget->RemoveFromParent();
}
