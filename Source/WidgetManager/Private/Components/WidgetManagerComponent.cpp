// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"


UWidgetManagerComponent::UWidgetManagerComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    CreateStartupWidgets();
    ShowStartupWidgets();
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    HideStartupWidgets();
    RemoveStartupWidgets();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UWidgetManagerComponent::CreateStartupWidgets()
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

void UWidgetManagerComponent::RemoveStartupWidgets()
{
    StartupWidgets.Empty();
}

void UWidgetManagerComponent::ShowStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        if (StartupWidget && !StartupWidget->IsInViewport())
        {
            StartupWidget->AddToViewport();
        }
    }
}

void UWidgetManagerComponent::HideStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        if (StartupWidget && StartupWidget->IsInViewport())
        {
            StartupWidget->RemoveFromParent();
        }
    }
}
