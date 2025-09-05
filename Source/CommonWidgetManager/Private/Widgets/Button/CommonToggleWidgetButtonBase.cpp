// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Button/CommonToggleWidgetButtonBase.h"

#include "Subsystems/CommonWidgetManagerSubsystem.h"

void UCommonToggleWidgetButtonBase::NativeOnClicked()
{
    Super::NativeOnClicked();

    if (UCommonWidgetManagerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCommonWidgetManagerSubsystem>())
    {
        Subsystem->ToggleLayerWidget(GetOwningPlayer(), LayerWidgetClass);
    }
}
