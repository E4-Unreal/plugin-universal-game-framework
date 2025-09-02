// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonAlertWidgetBase.h"

#include "CommonButtonBase.h"

void UCommonAlertWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetConfirmButton())
    {
        GetConfirmButton()->OnClicked().AddUObject(this, &ThisClass::OnConfirmButtonClicked);
    }
}

void UCommonAlertWidgetBase::OnConfirmButtonClicked_Implementation()
{
    DeactivateWidget();
}
