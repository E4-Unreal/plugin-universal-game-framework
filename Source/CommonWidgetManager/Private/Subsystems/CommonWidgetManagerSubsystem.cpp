// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonWidgetManagerSubsystem.h"

#include "Components/CommonWidgetManagerComponent.h"
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
        if (UCommonWidgetManagerComponent* CommonWidgetManager = PlayerController->GetComponentByClass<UCommonWidgetManagerComponent>())
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
        if (UCommonWidgetManagerComponent* CommonWidgetManager = PlayerController->GetComponentByClass<UCommonWidgetManagerComponent>())
        {
            CommonWidgetManager->ShowConfirmWidget(TitleText, MessageText, ConfirmButtonClickedDelegate);
        }
    }
}
