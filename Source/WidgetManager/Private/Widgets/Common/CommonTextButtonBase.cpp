// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Common/CommonTextButtonBase.h"

#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"

UCommonTextButtonBase::UCommonTextButtonBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Size = FVector2D(120, 40);
    Text = NSLOCTEXT("WidgetManager", "Button", "Button");
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
        GetSizeBox()->SetWidthOverride(Size.X);
        GetSizeBox()->SetHeightOverride(Size.Y);
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
