// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonTextButton.h"

#include "CommonTextBlock.h"

UCommonTextButton::UCommonTextButton(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ButtonText = FText::FromString(TEXT("Button"));
}

void UCommonTextButton::NativePreConstruct()
{
    Super::NativePreConstruct();

    ButtonTextBlock->SetText(ButtonText);
}

void UCommonTextButton::NativeOnCurrentTextStyleChanged()
{
    Super::NativeOnCurrentTextStyleChanged();

    if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
    {
        TSubclassOf<UCommonTextStyle> TextStyleClass = GetCurrentTextStyleClass();
        if (!TextStyleClass) TextStyleClass = CommonButtonStyle->NormalTextStyle;
        ButtonTextBlock->SetStyle(TextStyleClass);

        // TODO 버튼 크기 재조정 필요
    }
}
