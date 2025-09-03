// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CommonWidgetManagerSubsystem.h"

#include "Components/CommonPlayerWidgetManagerComponent.h"
#include "GameFramework/PlayerState.h"
#include "Widgets/CommonLayoutWidgetBase.h"

bool UCommonWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

APlayerController* UCommonWidgetManagerSubsystem::GetLocalPlayerController(AActor* PlayerActor) const
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

UCommonPlayerWidgetManagerComponent* UCommonWidgetManagerSubsystem::GetCommonPlayerWidgetManager(
    AActor* PlayerActor) const
{
    APlayerController* LocalPlayerController = GetLocalPlayerController(PlayerActor);

    return LocalPlayerController ? LocalPlayerController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>() : nullptr;
}

void UCommonWidgetManagerSubsystem::ShowAlertWidget(AActor* PlayerActor, const FText& TitleText,
                                                    const FText& MessageText)
{
    if (UCommonPlayerWidgetManagerComponent* CommonPlayerWidgetManager = GetCommonPlayerWidgetManager(PlayerActor))
    {
        CommonPlayerWidgetManager->ShowAlertWidget(TitleText, MessageText);
    }
}

void UCommonWidgetManagerSubsystem::ShowConfirmWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FButtonClickedDelegate& ConfirmButtonClickedDelegate)
{
    if (UCommonPlayerWidgetManagerComponent* CommonPlayerWidgetManager = GetCommonPlayerWidgetManager(PlayerActor))
    {
        CommonPlayerWidgetManager->ShowConfirmWidget(TitleText, MessageText, ConfirmButtonClickedDelegate);
    }
}

void UCommonWidgetManagerSubsystem::ShowPromptWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric, int64 MinNum, int64 MaxNum)
{
    if (UCommonPlayerWidgetManagerComponent* CommonPlayerWidgetManager = GetCommonPlayerWidgetManager(PlayerActor))
    {
        CommonPlayerWidgetManager->ShowPromptWidget(TitleText, MessageText, ConfirmButtonClickedDelegate, bShouldNumeric, MinNum, MaxNum);
    }
}

UCommonActivatableWidget* UCommonWidgetManagerSubsystem::ShowLayerWidget(AActor* PlayerActor,
    TSubclassOf<UCommonLayerWidgetBase> WidgetClass)
{
    UCommonPlayerWidgetManagerComponent* CommonPlayerWidgetManager = GetCommonPlayerWidgetManager(PlayerActor);

    return CommonPlayerWidgetManager ? CommonPlayerWidgetManager->ShowLayerWidget(WidgetClass) : nullptr;
}

bool UCommonWidgetManagerSubsystem::HideLayerWidget(AActor* PlayerActor,
    TSubclassOf<UCommonLayerWidgetBase> WidgetClass)
{
    UCommonPlayerWidgetManagerComponent* CommonPlayerWidgetManager = GetCommonPlayerWidgetManager(PlayerActor);

    return CommonPlayerWidgetManager ? CommonPlayerWidgetManager->HideLayerWidget(WidgetClass) : false;
}

void UCommonWidgetManagerSubsystem::ToggleLayerWidget(AActor* PlayerActor,
    TSubclassOf<UCommonLayerWidgetBase> WidgetClass)
{
    if (UCommonPlayerWidgetManagerComponent* CommonPlayerWidgetManager = GetCommonPlayerWidgetManager(PlayerActor))
    {
        CommonPlayerWidgetManager->ToggleLayerWidget(WidgetClass);
    }
}
