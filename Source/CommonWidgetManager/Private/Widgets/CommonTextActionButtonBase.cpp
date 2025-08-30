// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonTextActionButtonBase.h"

#include "CommonBorder.h"
#include "CommonTextBlock.h"

void UCommonTextActionButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetActionButtonNormal();
}

void UCommonTextActionButtonBase::NativeOnHovered()
{
    Super::NativeOnHovered();

    SetActionButtonHovered();
}

void UCommonTextActionButtonBase::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();

    SetActionButtonNormal();
}

void UCommonTextActionButtonBase::NativeOnPressed()
{
    Super::NativeOnPressed();

    SetActionButtonPressed();
}

void UCommonTextActionButtonBase::NativeOnReleased()
{
    Super::NativeOnReleased();

    SetActionButtonNormal();
}

void UCommonTextActionButtonBase::SetActionButtonNormal()
{
    if (ActionButtonStyle)
    {
        UCommonButtonStyle* ButtonStyle = Cast<UCommonButtonStyle>(ActionButtonStyle->ClassDefaultObject);
        if (GetSelected())
        {
            SetActionBorderBrush(ButtonStyle->SelectedBase);
            SetActionTextStyle(ButtonStyle->SelectedTextStyle);
        }
        else
        {
            SetActionBorderBrush(ButtonStyle->NormalBase);
            SetActionTextStyle(ButtonStyle->NormalTextStyle);
        }
    }
}

void UCommonTextActionButtonBase::SetActionButtonHovered()
{
    if (ActionButtonStyle)
    {
        UCommonButtonStyle* ButtonStyle = Cast<UCommonButtonStyle>(ActionButtonStyle->ClassDefaultObject);
        if (GetSelected())
        {
            SetActionBorderBrush(ButtonStyle->SelectedHovered);
            SetActionTextStyle(ButtonStyle->SelectedHoveredTextStyle);
        }
        else
        {
            SetActionBorderBrush(ButtonStyle->NormalHovered);
            SetActionTextStyle(ButtonStyle->NormalHoveredTextStyle);
        }
    }
}

void UCommonTextActionButtonBase::SetActionButtonPressed()
{
    if (ActionButtonStyle)
    {
        UCommonButtonStyle* ButtonStyle = Cast<UCommonButtonStyle>(ActionButtonStyle->ClassDefaultObject);
        if (GetSelected())
        {
            SetActionBorderBrush(ButtonStyle->SelectedPressed);
            SetActionTextStyle(ButtonStyle->SelectedTextStyle);
        }
        else
        {
            SetActionBorderBrush(ButtonStyle->NormalPressed);
            SetActionTextStyle(ButtonStyle->NormalTextStyle);
        }
    }
}

void UCommonTextActionButtonBase::SetActionBorderBrush(const FSlateBrush& NewBrush)
{
    if (GetActionBorder())
    {
        GetActionBorder()->SetBrush(NewBrush);
    }
}

void UCommonTextActionButtonBase::SetActionTextStyle(TSubclassOf<UCommonTextStyle> NewStyle)
{
    if (GetActionTextBlock())
    {
        GetActionTextBlock()->SetStyle(NewStyle);
    }
}
