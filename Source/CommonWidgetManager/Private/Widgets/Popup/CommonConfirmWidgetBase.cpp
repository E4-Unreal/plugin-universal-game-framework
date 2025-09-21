// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonConfirmWidgetBase.h"

#include "CommonButtonBase.h"

void UCommonConfirmWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetConfirmButton())
    {
        GetConfirmButton()->OnClicked().AddUObject(this, &ThisClass::HandleOnConfirmButtonClicked);
    }

    if (GetCancelButton())
    {
        GetCancelButton()->OnClicked().AddUObject(this, &ThisClass::HandleOnCancelButtonClicked);
    }
}

void UCommonConfirmWidgetBase::HandleOnConfirmButtonClicked_Implementation()
{
    DeactivateWidget();

    if (OnConfirmButtonClicked.IsBound())
    {
        OnConfirmButtonClicked.Execute();
        OnConfirmButtonClicked.Clear();
    }

    ConfirmButtonClickedEvent.Broadcast();
}

void UCommonConfirmWidgetBase::HandleOnCancelButtonClicked_Implementation()
{
    DeactivateWidget();

    CancelButtonClickedEvent.Broadcast();
}
