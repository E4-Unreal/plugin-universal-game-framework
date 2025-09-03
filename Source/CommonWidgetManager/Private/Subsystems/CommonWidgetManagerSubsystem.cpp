// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonWidgetManagerSubsystem.h"

#include "Components/CommonPlayerWidgetManagerComponent.h"
#include "Widgets/CommonLayoutWidgetBase.h"

bool UCommonWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

void UCommonWidgetManagerSubsystem::ShowAlertWidget(APlayerController* PlayerController, const FText& TitleText,
    const FText& MessageText)
{
    if (PlayerController && PlayerController->IsLocalController())
    {
        if (UCommonPlayerWidgetManagerComponent* CommonWidgetManager = PlayerController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>())
        {
            CommonWidgetManager->ShowAlertWidget(TitleText, MessageText);
        }
    }
}

void UCommonWidgetManagerSubsystem::ShowConfirmWidget(APlayerController* PlayerController, const FText& TitleText,
    const FText& MessageText, const FButtonClickedDelegate& ConfirmButtonClickedDelegate)
{
    if (PlayerController && PlayerController->IsLocalController())
    {
        if (UCommonPlayerWidgetManagerComponent* CommonWidgetManager = PlayerController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>())
        {
            CommonWidgetManager->ShowConfirmWidget(TitleText, MessageText, ConfirmButtonClickedDelegate);
        }
    }
}

void UCommonWidgetManagerSubsystem::ShowPromptWidget(APlayerController* PlayerController, const FText& TitleText,
    const FText& MessageText, const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric, int64 MinNum, int64 MaxNum)
{
    if (PlayerController && PlayerController->IsLocalController())
    {
        if (UCommonPlayerWidgetManagerComponent* CommonWidgetManager = PlayerController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>())
        {
            CommonWidgetManager->ShowPromptWidget(TitleText, MessageText, ConfirmButtonClickedDelegate, bShouldNumeric, MinNum, MaxNum);
        }
    }
}
