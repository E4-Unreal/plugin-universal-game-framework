// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/UGFInputConfig_UserWidget.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"

bool FUGFInputActionData::IsValid() const
{
    return InputAction && TriggerEvent != ETriggerEvent::None && WidgetClass;
}

void UUGFInputConfig_UserWidget::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (APlayerController* PlayerController = GetPlayerController(EnhancedInputComponent))
        {
            for (const auto& InputActionData : InputActionDataList)
            {
                if (InputActionData.IsValid())
                {
                    UUserWidget* Widget = CreateWidget(PlayerController, InputActionData.WidgetClass);
                    EnhancedInputComponent->BindAction(
                        InputActionData.InputAction,
                        InputActionData.TriggerEvent,
                        this,
                        &ThisClass::ToggleWidget,
                        Widget
                        );
                }
            }
        }
    }
}

void UUGFInputConfig_UserWidget::ToggleWidget(UUserWidget* Widget)
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
