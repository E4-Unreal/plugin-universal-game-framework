// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Button/CommonToggleWidgetButtonBase.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void UCommonToggleWidgetButtonBase::NativeOnClicked()
{
    Super::NativeOnClicked();

    if (auto Subsystem = GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        Subsystem->ToggleWidget(GetOwningPlayer(), WidgetClass);
    }
}
