// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnInputManagerComponentBase.h"

#include "EnhancedInputComponent.h"


UPawnInputManagerComponentBase::UPawnInputManagerComponentBase()
{
}

void UPawnInputManagerComponentBase::BeginPlay()
{
    Super::BeginPlay();

    BindInputActions();
    BindPawnRestartedEvent();
}

void UPawnInputManagerComponentBase::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    UnBindInputActions();
    UnBindPawnRestartedEvent();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UPawnInputManagerComponentBase::BindInputActions()
{
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(CastChecked<APawn>(GetOwner())->InputComponent);
    if (EnhancedInputComponent.IsValid())
    {
        const auto& InputActionConfigs = GetInputActionConfigs();
        InputActionBindingHandles.Reserve(InputActionConfigs.Num());
        for (const auto& [InputAction, TriggerEvents] : InputActionConfigs)
        {
            if (InputAction && !TriggerEvents.IsEmpty())
            {
                for (ETriggerEvent TriggerEvent : TriggerEvents)
                {
                    uint32 InputActionBindingHandle;
                    switch (TriggerEvent)
                    {
                    case ETriggerEvent::None:
                        continue;
                        break;
                    case ETriggerEvent::Triggered:
                        InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                            InputAction,
                            TriggerEvent,
                            [&](const FInputActionInstance& ActionInstance){ OnInputActionTriggered(ActionInstance); }).GetHandle();
                        break;
                    case ETriggerEvent::Started:
                        InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                            InputAction,
                            TriggerEvent,
                            [&](const FInputActionInstance& ActionInstance){ OnInputActionStarted(ActionInstance); }).GetHandle();
                        break;
                    case ETriggerEvent::Ongoing:
                        InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                            InputAction,
                            TriggerEvent,
                            [&](const FInputActionInstance& ActionInstance){ OnInputActionOngoing(ActionInstance); }).GetHandle();
                        break;
                    case ETriggerEvent::Canceled:
                        InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                            InputAction,
                            TriggerEvent,
                            [&](const FInputActionInstance& ActionInstance){ OnInputActionCanceled(ActionInstance); }).GetHandle();
                        break;
                    case ETriggerEvent::Completed:
                        InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                            InputAction,
                            TriggerEvent,
                            [&](const FInputActionInstance& ActionInstance){ OnInputActionCompleted(ActionInstance); }).GetHandle();
                        break;
                    }

                    InputActionBindingHandles.Emplace(InputActionBindingHandle);
                }
            }
        }
    }
}

void UPawnInputManagerComponentBase::UnBindInputActions()
{
    if (EnhancedInputComponent.IsValid() && !InputActionBindingHandles.IsEmpty())
    {
        for (int32 InputBindingHandle : InputActionBindingHandles)
        {
            EnhancedInputComponent->RemoveActionBindingForHandle(InputBindingHandle);
        }
        InputActionBindingHandles.Reset();
    }
}

void UPawnInputManagerComponentBase::OnInputActionTriggered_Implementation(
    const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputManagerComponentBase::OnInputActionStarted_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputManagerComponentBase::OnInputActionOngoing_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputManagerComponentBase::OnInputActionCanceled_Implementation(
    const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputManagerComponentBase::OnInputActionCompleted_Implementation(
    const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputManagerComponentBase::BindPawnRestartedEvent()
{
    CastChecked<APawn>(GetOwner())->ReceiveRestartedDelegate.AddDynamic(this, &ThisClass::OnOwningPawnRestarted);
}

void UPawnInputManagerComponentBase::UnBindPawnRestartedEvent()
{
    CastChecked<APawn>(GetOwner())->ReceiveRestartedDelegate.RemoveDynamic(this, &ThisClass::OnOwningPawnRestarted);
}

void UPawnInputManagerComponentBase::OnOwningPawnRestarted(APawn* OwningPawn)
{
    UnBindInputActions();
    BindInputActions();
}
