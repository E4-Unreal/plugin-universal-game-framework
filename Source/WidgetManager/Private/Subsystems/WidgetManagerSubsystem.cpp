// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/WidgetManagerSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Components/PlayerWidgetManagerComponent.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/AlertWidgetInterface.h"
#include "Interfaces/ConfirmWidgetInterface.h"
#include "Interfaces/PromptWidgetInterface.h"
#include "Settings/WidgetManagerSettings.h"

bool UWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

APlayerController* UWidgetManagerSubsystem::GetLocalPlayerController(AActor* PlayerActor) const
{
    APlayerController* PlayerController = nullptr;

    if (PlayerActor)
    {
        if (PlayerActor->IsA(APlayerController::StaticClass()))
        {
            PlayerController = Cast<APlayerController>(PlayerActor);
        }
        else if (PlayerActor->IsA(APawn::StaticClass()))
        {
            PlayerController = Cast<APlayerController>(Cast<APawn>(PlayerActor)->GetController());
        }
        else if (PlayerActor->IsA(APlayerState::StaticClass()))
        {
            PlayerController = Cast<APlayerState>(PlayerActor)->GetPlayerController();
        }
    }

    return PlayerController && PlayerController->IsLocalController() ? PlayerController : nullptr;
}

UPlayerWidgetManagerComponent* UWidgetManagerSubsystem::GetPlayerWidgetManager(AActor* PlayerActor) const
{
    APlayerController* LocalPlayerController = GetLocalPlayerController(PlayerActor);

    return LocalPlayerController ? LocalPlayerController->GetComponentByClass<UPlayerWidgetManagerComponent>() : nullptr;
}

UUserWidget* UWidgetManagerSubsystem::ShowAlertWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UAlertWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultAlertWidgetClass();
    auto PlayerWidgetManager = GetPlayerWidgetManager(PlayerActor);

    if (WidgetClass && PlayerWidgetManager)
    {
        if (UUserWidget* Widget = PlayerWidgetManager->ShowWidget(WidgetClass))
        {
            IAlertWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IAlertWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IAlertWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

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
    auto PlayerWidgetManager = GetPlayerWidgetManager(PlayerActor);

    if (WidgetClass && PlayerWidgetManager)
    {
        if (UUserWidget* Widget = PlayerWidgetManager->ShowWidget(WidgetClass))
        {
            IConfirmWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IConfirmWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IConfirmWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);
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
    auto PlayerWidgetManager = GetPlayerWidgetManager(PlayerActor);

    if (WidgetClass && PlayerWidgetManager)
    {
        if (UUserWidget* Widget = PlayerWidgetManager->ShowWidget(WidgetClass))
        {
            IPromptWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPromptWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPromptWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);
            IPromptWidgetInterface::Execute_BindOnPromptSubmitted(Widget, PromptSubmittedDelegate);
            IPromptWidgetInterface::Execute_SetNumeric(Widget, bNumeric);
            IPromptWidgetInterface::Execute_SetMinValue(Widget, MinValue);
            IPromptWidgetInterface::Execute_SetMaxValue(Widget, MaxValue);

            return Widget;
        }
    }

    return nullptr;
}

UUserWidget* UWidgetManagerSubsystem::ShowWidget(AActor* PlayerActor, TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto PlayerWidgetManager = GetPlayerWidgetManager(PlayerActor))
    {
        return PlayerWidgetManager->ShowWidget(WidgetClass);
    }

    return nullptr;
}

bool UWidgetManagerSubsystem::HideWidget(AActor* PlayerActor, TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto PlayerWidgetManager = GetPlayerWidgetManager(PlayerActor))
    {
        return PlayerWidgetManager->HideWidget(WidgetClass);
    }

    return false;
}

void UWidgetManagerSubsystem::ToggleWidget(AActor* PlayerActor, TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto PlayerWidgetManager = GetPlayerWidgetManager(PlayerActor))
    {
        PlayerWidgetManager->ToggleWidget(WidgetClass);
    }
}
