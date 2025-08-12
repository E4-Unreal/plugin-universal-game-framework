// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponentBase.h"

#include "Blueprint/UserWidget.h"

UWidgetManagerComponentBase::UWidgetManagerComponentBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UWidgetManagerComponentBase::BeginPlay()
{
    Super::BeginPlay();

    CreateStartupWidgets();
    ShowStartupWidgets();
}

void UWidgetManagerComponentBase::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    HideStartupWidgets();
    RemoveStartupWidgets();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UWidgetManagerComponentBase::ShowWidget(UUserWidget* Widget)
{
    if (Widget && !Widget->IsInViewport())
    {
        Widget->AddToViewport();
    }
}

void UWidgetManagerComponentBase::HideWidget(UUserWidget* Widget)
{
    if (Widget && Widget->IsInViewport())
    {
        Widget->RemoveFromParent();
    }
}

void UWidgetManagerComponentBase::ToggleWidget(UUserWidget* Widget)
{
    if (Widget)
    {
        if (Widget->IsInViewport())
        {
            Widget->RemoveFromParent();
        }
        else
        {
            Widget->AddToViewport();
        }
    }
}

void UWidgetManagerComponentBase::CreateStartupWidgets()
{
    if (!StartupWidgets.IsEmpty()) return;

    StartupWidgets.Reserve(StartupWidgetClasses.Num());
    for (TSubclassOf<UUserWidget> StartupWidgetClass : StartupWidgetClasses)
    {
        if (StartupWidgetClass)
        {
            UUserWidget* StartupWidget = CreateWidget<UUserWidget>(GetWorld(), StartupWidgetClass);
            StartupWidgets.Emplace(StartupWidget);
        }
    }
}

void UWidgetManagerComponentBase::RemoveStartupWidgets()
{
    StartupWidgets.Empty();
}

void UWidgetManagerComponentBase::ShowStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        ShowWidget(StartupWidget);
    }
}

void UWidgetManagerComponentBase::HideStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        HideWidget(StartupWidget);
    }
}

void UWidgetManagerComponentBase::ToggleStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        ToggleWidget(StartupWidget);
    }
}
