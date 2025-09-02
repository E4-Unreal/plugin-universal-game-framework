// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonConfirmWidgetBase.h"

#include "CommonButtonBase.h"

void UCommonConfirmWidgetBase::NativeOnInitialized()
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

void UCommonConfirmWidgetBase::OnConfirmButtonClicked_Implementation()
{
    DeactivateWidget();

    if (ConfirmButtonClickedDelegate.IsBound())
    {
        ConfirmButtonClickedDelegate.Execute();
        ConfirmButtonClickedDelegate.Clear();
    }

    ConfirmButtonClickedEvent.Broadcast();
}

void UCommonConfirmWidgetBase::OnCancelButtonClicked_Implementation()
{
    DeactivateWidget();

    if (CancelButtonClickedDelegate.IsBound())
    {
        CancelButtonClickedDelegate.Execute();
        CancelButtonClickedDelegate.Clear();
    }

    CancelButtonClickedEvent.Broadcast();
}
