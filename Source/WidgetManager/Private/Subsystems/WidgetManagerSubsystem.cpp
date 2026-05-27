// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/WidgetManagerSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/AlertWidgetInterface.h"
#include "Interfaces/ConfirmWidgetInterface.h"
#include "Interfaces/LayoutWidgetInterface.h"
#include "Interfaces/PromptWidgetInterface.h"
#include "Settings/WidgetManagerSettings.h"

UWidgetManagerSubsystem* UWidgetManagerSubsystem::Get(UObject* ContextObject)
{
    if (ContextObject == nullptr) return nullptr;

    const ULocalPlayer* LocalPlayer = nullptr;

    if (ContextObject->IsA<UUserWidget>())
    {
        LocalPlayer = Cast<UUserWidget>(ContextObject)->GetOwningLocalPlayer();
    }
    else if (ContextObject->IsA<ULocalPlayer>())
    {
        LocalPlayer = Cast<ULocalPlayer>(ContextObject);
    }
    else if (ContextObject->IsA<UActorComponent>())
    {
        const AActor* Actor = Cast<UActorComponent>(ContextObject)->GetOwner();
        const APlayerController* PlayerController = nullptr;

        if (Actor->IsA<APlayerController>())
        {
            PlayerController = Cast<APlayerController>(Actor);
        }
        else if (Actor->IsA<APlayerState>())
        {
            PlayerController = Cast<APlayerState>(Actor)->GetPlayerController();
        }
        else if (Actor->IsA<APawn>())
        {
            PlayerController = Cast<APlayerController>(Cast<APawn>(Actor)->GetController());
        }
        else
        {
            PlayerController = Cast<APlayerController>(Actor->GetInstigatorController());
        }

        LocalPlayer = PlayerController ? PlayerController->GetLocalPlayer() : nullptr;
    }

    return LocalPlayer ? LocalPlayer->GetSubsystem<ThisClass>() : nullptr;
}

bool UWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

void UWidgetManagerSubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
    Super::PlayerControllerChanged(NewPlayerController);

    DestroyLayoutWidget();
    CreateLayoutWidget(NewPlayerController);
}

UUserWidget* UWidgetManagerSubsystem::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        return ILayoutWidgetInterface::Execute_ShowWidget(LayoutWidget, WidgetClass);
    }

    return nullptr;
}

bool UWidgetManagerSubsystem::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        return ILayoutWidgetInterface::Execute_HideWidget(LayoutWidget, WidgetClass);
    }

    return false;
}

void UWidgetManagerSubsystem::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        ILayoutWidgetInterface::Execute_ToggleWidget(LayoutWidget, WidgetClass);
    }
}

void UWidgetManagerSubsystem::ExecuteBackAction()
{
    if (LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        ILayoutWidgetInterface::Execute_ExecuteBackAction(LayoutWidget);
    }
}

UUserWidget* UWidgetManagerSubsystem::ShowAlertWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UAlertWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultAlertWidgetClass();

    if (WidgetClass)
    {
        if (UUserWidget* Widget = ShowWidget(WidgetClass))
        {
            IPopupWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPopupWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPopupWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

            return Widget;
        }
    }

    return nullptr;
}

UUserWidget* UWidgetManagerSubsystem::ShowConfirmWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate,
    const FOnButtonClicked& ConfirmButtonClickedDelegate, TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UConfirmWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultConfirmWidgetClass();

    if (WidgetClass)
    {
        if (UUserWidget* Widget = ShowWidget(WidgetClass))
        {
            IPopupWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPopupWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPopupWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

            IConfirmWidgetInterface::Execute_BindOnConfirmButtonClicked(Widget, ConfirmButtonClickedDelegate);

            return Widget;
        }
    }

    return nullptr;
}

UUserWidget* UWidgetManagerSubsystem::ShowPromptWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate,
    const FOnPromptSubmitted& PromptSubmittedDelegate, bool bNumeric, float MinValue, float MaxValue,
    TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UPromptWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultPromptWidgetClass();

    if (WidgetClass)
    {
        if (UUserWidget* Widget = ShowWidget(WidgetClass))
        {
            IPopupWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPopupWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPopupWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

            IPromptWidgetInterface::Execute_BindOnPromptSubmitted(Widget, PromptSubmittedDelegate);
            IPromptWidgetInterface::Execute_SetNumeric(Widget, bNumeric);
            IPromptWidgetInterface::Execute_SetMinValue(Widget, MinValue);
            IPromptWidgetInterface::Execute_SetMaxValue(Widget, MaxValue);

            return Widget;
        }
    }

    return nullptr;
}

void UWidgetManagerSubsystem::CreateLayoutWidget(APlayerController* PlayerController)
{
    if (auto Settings = UWidgetManagerSettings::Get())
    {
        if (TSubclassOf<UUserWidget> LayoutWidgetClass = Settings->GetLayoutWidgetClass())
        {
            LayoutWidget = CreateWidget<UUserWidget>(PlayerController, LayoutWidgetClass);
            LayoutWidget->AddToViewport();
        }
    }
}

void UWidgetManagerSubsystem::DestroyLayoutWidget()
{
    if (LayoutWidget)
    {
        LayoutWidget->RemoveFromParent();
        LayoutWidget = nullptr;
    }
}
