// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonPopupWidgetBase.h"

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"

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

void UCommonPopupWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetConfirmButton())
    {
        GetConfirmButton()->OnClicked().AddUObject(this, &ThisClass::OnConfirmButtonClicked);
    }

    if (GetCancelButton())
    {
        GetCancelButton()->OnClicked().AddUObject(this, &ThisClass::OnCancelButtonClicked);
    }
}

void UCommonPopupWidgetBase::OnConfirmButtonClicked_Implementation()
{
    if (ConfirmButtonClickedDelegate.IsBound())
    {
        ConfirmButtonClickedDelegate.Execute();
        ConfirmButtonClickedDelegate.Clear();
    }

    ConfirmButtonClickedEvent.Broadcast();

    DeactivateWidget();
}

void UCommonPopupWidgetBase::OnCancelButtonClicked_Implementation()
{
    if (CancelButtonClickedDelegate.IsBound())
    {
        CancelButtonClickedDelegate.Execute();
        CancelButtonClickedDelegate.Clear();
    }

    CancelButtonClickedEvent.Broadcast();

    DeactivateWidget();
}
