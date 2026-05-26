// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonTextButtonBase.h"

#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"

UCommonTextButtonBase::UCommonTextButtonBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* TextBlock */

    TextOverride = NSLOCTEXT("WidgetManager", "Button", "Button");
    HorizontalAlignmentOverride = HAlign_Center;
    VerticalAlignmentOverride = VAlign_Center;
    PaddingOverride = FMargin(12.0f, 6.f);

    /* SizeBox */

    // Width: 120, 160, 200, 240, 280, 320
    // Height: 40, 48, 56, 60

    bOverride_Width = true;
    bOverride_Height = true;
    WidthOverride = 120.0f;
    HeightOverride = 40.0f;

    bOverride_MinDesiredWidth = false;
    bOverride_MinDesiredHeight = false;
    MinDesiredWidthOverride = 0.0f;
    MinDesiredHeightOverride = 0.0f;

    bOverride_MaxDesiredWidth = false;
    bOverride_MaxDesiredHeight = false;
    MaxDesiredWidthOverride = 0.0f;
    MaxDesiredHeightOverride = 0.0f;

    bOverride_MinAspectRatio = false;
    bOverride_MaxAspectRatio = false;
    MinAspectRatioOverride = 0.0f;
    MaxAspectRatioOverride = 0.0f;
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
        if (bOverride_Width) GetSizeBox()->SetWidthOverride(WidthOverride);
        if (bOverride_Height) GetSizeBox()->SetHeightOverride(HeightOverride);
        if (bOverride_MinDesiredWidth) GetSizeBox()->SetMinDesiredWidth(MinDesiredWidthOverride);
        if (bOverride_MinDesiredHeight) GetSizeBox()->SetMinDesiredHeight(MinDesiredHeightOverride);
        if (bOverride_MaxDesiredWidth) GetSizeBox()->SetMaxDesiredWidth(MaxDesiredWidthOverride);
        if (bOverride_MaxDesiredHeight) GetSizeBox()->SetMaxDesiredHeight(MaxDesiredHeightOverride);
        if (bOverride_MinAspectRatio) GetSizeBox()->SetMinAspectRatio(MinAspectRatioOverride);
        if (bOverride_MaxAspectRatio) GetSizeBox()->SetMaxAspectRatio(MaxAspectRatioOverride);
    }

    if (GetTextBlock())
    {
        GetTextBlock()->SetText(TextOverride);
        GetTextBlock()->SetStyle(GetDefaultTextStyleClass());

        if (auto TextSlot = Cast<USizeBoxSlot>(GetTextBlock()->Slot))
        {
            TextSlot->SetHorizontalAlignment(HorizontalAlignmentOverride);
            TextSlot->SetVerticalAlignment(VerticalAlignmentOverride);
            TextSlot->SetPadding(PaddingOverride);
        }
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
