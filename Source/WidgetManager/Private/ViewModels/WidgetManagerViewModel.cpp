// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/WidgetManagerViewModel.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void UWidgetManagerViewModel::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->ShowWidget(WidgetClass);
    }
}

void UWidgetManagerViewModel::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->HideWidget(WidgetClass);
    }
}

void UWidgetManagerViewModel::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->ToggleWidget(WidgetClass);
    }
}
