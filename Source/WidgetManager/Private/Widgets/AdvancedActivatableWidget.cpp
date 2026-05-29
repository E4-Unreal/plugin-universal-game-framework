// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/AdvancedActivatableWidget.h"

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
