// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AdvancedActivatableWidget.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void UAdvancedActivatableWidget::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(this))
    {
        Subsystem->ShowWidget(WidgetClass);
    }
}

void UAdvancedActivatableWidget::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(this))
    {
        Subsystem->HideWidget(WidgetClass);
    }
}

void UAdvancedActivatableWidget::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(this))
    {
        Subsystem->ToggleWidget(WidgetClass);
    }
}

bool UAdvancedActivatableWidget::NativeOnHandleBackAction()
{
    if (bIsBackHandler)
    {
        if (OnBackActionTriggered.IsBound())
        {
            OnBackActionTriggered.Broadcast();
        }
        else if (!BP_OnHandleBackAction())
        {
            DeactivateWidget();
        }
        return true;
    }
    return false;
}
