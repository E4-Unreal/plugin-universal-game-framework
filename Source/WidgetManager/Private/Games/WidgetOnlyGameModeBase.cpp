// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/WidgetOnlyGameModeBase.h"

#include "Blueprint/UserWidget.h"

AWidgetOnlyGameModeBase::AWidgetOnlyGameModeBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    DefaultPawnClass = nullptr;
    SpectatorClass = nullptr;
}

void AWidgetOnlyGameModeBase::Destroyed()
{
    DestroyWidgets();

    Super::Destroyed();
}

void AWidgetOnlyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    CreateWidgets();
    ShowWidgets();
    SetPlayerUIMode();
}

void AWidgetOnlyGameModeBase::CreateWidgets()
{
    Widgets.Reset(WidgetClasses.Num());
    for (TSubclassOf<UUserWidget> WidgetClass : WidgetClasses)
    {
        if (WidgetClass == nullptr) continue;

        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        Widgets.Emplace(Widget);
    }
}

void AWidgetOnlyGameModeBase::DestroyWidgets()
{
    for (UUserWidget* Widget : Widgets)
    {
        if (Widget->IsInViewport())
        {
            Widget->RemoveFromParent();
        }
    }
    Widgets.Empty();
}

void AWidgetOnlyGameModeBase::ShowWidgets()
{
    for (UUserWidget* Widget : Widgets)
    {
        if (!Widget->IsInViewport())
        {
            Widget->AddToViewport();
        }

        if (!Widget->IsVisible())
        {
            Widget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void AWidgetOnlyGameModeBase::HideWidgets()
{
    for (UUserWidget* Widget : Widgets)
    {
        if (Widget->IsVisible())
        {
            Widget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void AWidgetOnlyGameModeBase::SetPlayerUIMode()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        PlayerController->SetShowMouseCursor(true);
        PlayerController->SetIgnoreMoveInput(true);
        PlayerController->SetIgnoreLookInput(true);
    }
}

