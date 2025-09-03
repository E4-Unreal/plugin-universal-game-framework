// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommonPlayerWidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/CommonLayoutWidgetBase.h"
#include "Widgets/Popup/CommonAlertWidgetBase.h"
#include "Widgets/Popup/CommonConfirmWidgetBase.h"
#include "Widgets/Popup/CommonPromptWidgetBase.h"

UCommonPlayerWidgetManagerComponent::UCommonPlayerWidgetManagerComponent()
{

}

void UCommonPlayerWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* OwningPlayerController = GetOwningPlayerController())
    {
        if (LayoutWidgetClass)
        {
            LayoutWidget = CreateWidget<UCommonLayoutWidgetBase>(OwningPlayerController, LayoutWidgetClass);
            LayoutWidget->AddToViewport();
        }
    }
}

void UCommonPlayerWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    if (LayoutWidget)
    {
        LayoutWidget->RemoveFromParent();
    }

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

APlayerController* UCommonPlayerWidgetManagerComponent::GetOwningPlayerController() const
{
    APlayerController* OwningPlayerController = nullptr;
    if (AActor* OwningActor = GetOwner())
    {
        if (OwningActor->IsA(APlayerController::StaticClass()))
        {
            OwningPlayerController = Cast<APlayerController>(OwningActor);
        }
        else if (OwningActor->IsA(APawn::StaticClass()))
        {
            APawn* OwningPawn = Cast<APawn>(OwningActor);
            OwningPlayerController = Cast<APlayerController>(OwningPawn->GetController());
        }

        if (OwningPlayerController && !OwningPlayerController->IsLocalController())
        {
            OwningPlayerController = nullptr;
        }
    }

    return OwningPlayerController;
}

void UCommonPlayerWidgetManagerComponent::ShowAlertWidget(const FText& TitleText, const FText& MessageText)
{
    if (GetLayoutWidget() && AlertWidgetClass)
    {
        if (UCommonAlertWidgetBase* AlertWidget = Cast<UCommonAlertWidgetBase>(GetLayoutWidget()->ShowLayerWidget(AlertWidgetClass)))
        {
            AlertWidget->SetTitleText(TitleText);
            AlertWidget->SetMessageText(MessageText);
        }
    }
}

void UCommonPlayerWidgetManagerComponent::ShowConfirmWidget(const FText& TitleText, const FText& MessageText,
    const FButtonClickedDelegate& ConfirmButtonClickedDelegate)
{
    if (GetLayoutWidget() && ConfirmWidgetClass)
    {
        if (UCommonConfirmWidgetBase* ConfirmWidget = Cast<UCommonConfirmWidgetBase>(GetLayoutWidget()->ShowLayerWidget(ConfirmWidgetClass)))
        {
            ConfirmWidget->SetTitleText(TitleText);
            ConfirmWidget->SetMessageText(MessageText);
            ConfirmWidget->SetConfirmButtonClickedDelegate(ConfirmButtonClickedDelegate);
        }
    }
}

void UCommonPlayerWidgetManagerComponent::ShowPromptWidget(const FText& TitleText, const FText& MessageText,
    const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric, int64 MinNum, int64 MaxNum)
{
    if (GetLayoutWidget() && PromptWidgetClass)
    {
        if (UCommonPromptWidgetBase* PromptWidget = Cast<UCommonPromptWidgetBase>(GetLayoutWidget()->ShowLayerWidget(PromptWidgetClass)))
        {
            PromptWidget->SetTitleText(TitleText);
            PromptWidget->SetMessageText(MessageText);
            PromptWidget->SetConfirmButtonClickedDelegate(ConfirmButtonClickedDelegate);
            PromptWidget->bShouldNumeric = bShouldNumeric;
            PromptWidget->MinNum = MinNum;
            PromptWidget->MaxNum = MaxNum;
        }
    }
}
