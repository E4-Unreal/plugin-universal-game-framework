// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnInputBinderComponentBase.h"

#include "EnhancedInputComponent.h"


UPawnInputBinderComponentBase::UPawnInputBinderComponentBase()
{
}

void UPawnInputBinderComponentBase::BeginPlay()
{
    Super::BeginPlay();

    BindInputActions();
    BindPawnRestartedEvent();
}

void UPawnInputBinderComponentBase::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    UnBindInputActions();
    UnBindPawnRestartedEvent();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UPawnInputBinderComponentBase::BindInputActions()
{
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(CastChecked<APawn>(GetOwner())->InputComponent);
    if (EnhancedInputComponent.IsValid())
    {
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

void UPawnInputBinderComponentBase::UnBindInputActions()
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

void UPawnInputBinderComponentBase::OnInputActionTriggered_Implementation(
    const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputBinderComponentBase::OnInputActionStarted_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputBinderComponentBase::OnInputActionOngoing_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputBinderComponentBase::OnInputActionCanceled_Implementation(
    const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputBinderComponentBase::OnInputActionCompleted_Implementation(
    const FInputActionInstance& InputActionInstance)
{
}

void UPawnInputBinderComponentBase::BindPawnRestartedEvent()
{
    CastChecked<APawn>(GetOwner())->ReceiveRestartedDelegate.AddDynamic(this, &ThisClass::OnOwningPawnRestarted);
}

void UPawnInputBinderComponentBase::UnBindPawnRestartedEvent()
{
    CastChecked<APawn>(GetOwner())->ReceiveRestartedDelegate.RemoveDynamic(this, &ThisClass::OnOwningPawnRestarted);
}

void UPawnInputBinderComponentBase::OnOwningPawnRestarted(APawn* OwningPawn)
{
    UnBindInputActions();
    BindInputActions();
}
