// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponent.h"

#include "Subsystems/WidgetManagerSubsystem.h"


UWidgetManagerComponent::UWidgetManagerComponent()
{
}

void UWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    for (TSubclassOf<UUserWidget> DefaultWidgetClass : DefaultWidgetClasses)
    {
        ShowWidget(DefaultWidgetClass);
    }
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    for (TSubclassOf<UUserWidget> DefaultWidgetClass : DefaultWidgetClasses)
    {
        HideWidget(DefaultWidgetClass);
    }

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UWidgetManagerComponent::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(this))
    {
        Subsystem->ShowWidget(WidgetClass);
    }
}

bool UWidgetManagerComponent::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(this))
    {
        return Subsystem->HideWidget(WidgetClass);
    }

    return false;
}

void UWidgetManagerComponent::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(this))
    {
        Subsystem->ToggleWidget(WidgetClass);
    }
}
