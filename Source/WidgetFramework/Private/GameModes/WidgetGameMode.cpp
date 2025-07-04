// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/WidgetGameMode.h"

#include "Blueprint/UserWidget.h"

void AWidgetGameMode::BeginPlay()
{
    Super::BeginPlay();

    CreateWidgets();
    ShowWidgets();
}

void AWidgetGameMode::CreateWidgets()
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

void AWidgetGameMode::RemoveWidgets()
{
    HideWidgets();

    Widgets.Reset();
}

void AWidgetGameMode::ToggleWidgets()
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

void AWidgetGameMode::ShowWidgets()
{
    if (bVisible) return;
    bVisible = true;

    for (TObjectPtr<UUserWidget> Widget : Widgets)
    {
        Widget->AddToViewport();
    }
}

void AWidgetGameMode::HideWidgets()
{
    if (!bVisible) return;
    bVisible = false;

    for (TObjectPtr<UUserWidget> Widget : Widgets)
    {
        Widget->RemoveFromParent();
    }
}
