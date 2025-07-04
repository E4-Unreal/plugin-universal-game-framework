// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/WidgetLevelActor.h"

#include "Blueprint/UserWidget.h"

void AWidgetLevelActor::BeginPlay()
{
    Super::BeginPlay();

    CreateWidgets();
    ShowWidgets();
}

void AWidgetLevelActor::BeginDestroy()
{
    Super::BeginDestroy();

    RemoveWidgets();
}

void AWidgetLevelActor::CreateWidgets()
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

void AWidgetLevelActor::RemoveWidgets()
{
    HideWidgets();

    Widgets.Reset();
}

void AWidgetLevelActor::ToggleWidgets()
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

void AWidgetLevelActor::ShowWidgets()
{
    if (bVisible) return;
    bVisible = true;

    for (TObjectPtr<UUserWidget> Widget : Widgets)
    {
        Widget->AddToViewport();
    }
}

void AWidgetLevelActor::HideWidgets()
{
    if (!bVisible) return;
    bVisible = false;

    for (TObjectPtr<UUserWidget> Widget : Widgets)
    {
        Widget->RemoveFromParent();
    }
}
