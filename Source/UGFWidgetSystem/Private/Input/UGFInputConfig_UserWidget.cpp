// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/UGFInputConfig_UserWidget.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/UGFWidgetManagerComponent.h"

bool FUGFInputActionData::IsValid() const
{
    return InputAction && TriggerEvent != ETriggerEvent::None && WidgetClass;
}

UUGFWidgetManagerComponent* UUGFInputConfig_UserWidget::GetWidgetManagerComponent(
    UEnhancedInputComponent* EnhancedInputComponent)
{
    if (APawn* OwningPlayerPawn = GetOwningPlayerPawn(EnhancedInputComponent))
    {
        return OwningPlayerPawn->GetComponentByClass<UUGFWidgetManagerComponent>();
    }

    return nullptr;
}

void UUGFInputConfig_UserWidget::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    APlayerController* PlayerController = GetOwningPlayer(EnhancedInputComponent);
    UUGFWidgetManagerComponent* WidgetManagerComponent = GetWidgetManagerComponent(EnhancedInputComponent);

    if (PlayerController && WidgetManagerComponent)
    {
        for (const auto& InputActionData : InputActionDataList)
        {
            if (InputActionData.IsValid())
            {
                EnhancedInputComponent->BindAction(
                    InputActionData.InputAction,
                    InputActionData.TriggerEvent,
                    WidgetManagerComponent,
                    &UUGFWidgetManagerComponent::ToggleWidget,
                    InputActionData.WidgetClass
                    );
            }
        }
    }
}
