// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/AdvancedViewModel.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void UAdvancedViewModel::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->ShowWidget(WidgetClass);
    }
}

void UAdvancedViewModel::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->HideWidget(WidgetClass);
    }
}

void UAdvancedViewModel::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->ToggleWidget(WidgetClass);
    }
}
