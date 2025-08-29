// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonTextButtonBase.h"

#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"

UCommonTextButtonBase::UCommonTextButtonBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Text = NSLOCTEXT("WidgetManager", "Button", "Button");

    // Width: 120, 160, 200, 240, 280, 320
    // Height: 40, 48, 56, 60

    bOverride_MinDesiredWidth = true;
    bOverride_MinDesiredHeight = true;
    MinDesiredWidth = 120;
    MinDesiredHeight = 40;

    bOverride_MaxDesiredWidth = true;
    bOverride_MaxDesiredHeight = true;
    MaxDesiredWidth = 320;
    MaxDesiredHeight = 60;
}

TSubclassOf<UCommonTextStyle> UCommonTextButtonBase::GetDefaultTextStyleClass() const
{
    TSubclassOf<UCommonTextStyle> DefaultTextStyleClass = nullptr;

    if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
    {
        if (UCommonTextStyle* DefaultTextStyle = CommonButtonStyle->GetNormalTextStyle())
        {
            DefaultTextStyleClass = DefaultTextStyle->GetClass();
        }
    }

    return DefaultTextStyleClass;
}

void UCommonTextButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (GetSizeBox())
    {
        if (bOverride_WidthOverride) GetSizeBox()->SetWidthOverride(WidthOverride);
        if (bOverride_HeightOverride) GetSizeBox()->SetHeightOverride(HeightOverride);
        if (bOverride_MinDesiredWidth) GetSizeBox()->SetMinDesiredWidth(MinDesiredWidth);
        if (bOverride_MinDesiredHeight) GetSizeBox()->SetMinDesiredHeight(MinDesiredHeight);
        if (bOverride_MaxDesiredWidth) GetSizeBox()->SetMaxDesiredWidth(MaxDesiredWidth);
        if (bOverride_MaxDesiredHeight) GetSizeBox()->SetMaxDesiredHeight(MaxDesiredHeight);
        if (bOverride_MinAspectRatio) GetSizeBox()->SetMinAspectRatio(MinAspectRatio);
        if (bOverride_MaxAspectRatio) GetSizeBox()->SetMaxAspectRatio(MaxAspectRatio);
    }

    if (GetTextBlock())
    {
        GetTextBlock()->SetText(Text);
        GetTextBlock()->SetStyle(GetDefaultTextStyleClass());
    }
}

void UCommonTextButtonBase::NativeOnCurrentTextStyleChanged()
{
    if (GetTextBlock())
    {
        TSubclassOf<UCommonTextStyle> NewTextStyleClass = GetCurrentTextStyleClass();
        if (NewTextStyleClass == nullptr) NewTextStyleClass = GetDefaultTextStyleClass();

        GetTextBlock()->SetStyle(NewTextStyleClass);
    }

    Super::NativeOnCurrentTextStyleChanged();
}
