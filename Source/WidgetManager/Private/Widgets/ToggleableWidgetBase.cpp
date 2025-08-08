// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ToggleableWidgetBase.h"

UToggleableWidgetBase::UToggleableWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetIsFocusable(true);
}

void UToggleableWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    SetFocus();
    SetKeyboardFocus();
}

FReply UToggleableWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    SetFocus();
    SetKeyboardFocus();

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UToggleableWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Escape)
    {
        RemoveFromParent();
        return FReply::Handled();
    }

    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
