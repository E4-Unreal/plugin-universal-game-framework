// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/WidgetPlayerController.h"

#include "Blueprint/UserWidget.h"

void AWidgetPlayerController::BeginPlay()
{
    Super::BeginPlay();

    CreateWidgets();
    ShowWidgets();
}

void AWidgetPlayerController::BeginDestroy()
{
    Super::BeginDestroy();

    RemoveWidgets();
}

void AWidgetPlayerController::CreateWidgets()
{
    RemoveWidgets();
    Widgets.Reserve(WidgetClasses.Num());

    for (TSubclassOf<UUserWidget> WidgetClass : WidgetClasses)
    {
        if (!WidgetClass) continue;

        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        Widgets.Emplace(Widget);
    }
}

void AWidgetPlayerController::RemoveWidgets()
{
    HideWidgets();

    Widgets.Reset();
}

void AWidgetPlayerController::ToggleWidgets()
{
    if (!bVisible)
    {
        ShowWidgets();
    }
    else
    {
        HideWidgets();
    }
}

void AWidgetPlayerController::ShowWidgets()
{
    if (bVisible) return;
    bVisible = true;

    for (TObjectPtr<UUserWidget> Widget : Widgets)
    {
        Widget->AddToViewport();
    }
}

void AWidgetPlayerController::HideWidgets()
{
    if (!bVisible) return;
    bVisible = false;

    for (TObjectPtr<UUserWidget> Widget : Widgets)
    {
        Widget->RemoveFromParent();
    }
}
