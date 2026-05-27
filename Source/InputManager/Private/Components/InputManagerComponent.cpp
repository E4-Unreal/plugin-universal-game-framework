// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Types/InputActionConfigData.h"

UInputManagerComponent::UInputManagerComponent()
{
}

void UInputManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    AddMappingContexts(DefaultMappingContexts);
    BindInputActions();
}

void UInputManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    UnbindInputActions();
    RemoveMappingContexts(DefaultMappingContexts);

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UInputManagerComponent::AddMappingContext(const UInputMappingContext* MappingContext, int32 Priority,
    const FModifyContextOptions& Options)
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        Subsystem->AddMappingContext(MappingContext, Priority, Options);
    }
}

void UInputManagerComponent::AddMappingContexts(const TArray<UInputMappingContext*>& MappingContexts, int32 Priority,
    const FModifyContextOptions& Options)
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (UInputMappingContext* MappingContext : MappingContexts)
        {
            Subsystem->AddMappingContext(MappingContext, Priority, Options);
        }
    }
}

void UInputManagerComponent::RemoveMappingContext(const UInputMappingContext* MappingContext,
                                                  const FModifyContextOptions& Options)
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        Subsystem->RemoveMappingContext(MappingContext, Options);
    }
}

void UInputManagerComponent::RemoveMappingContexts(const TArray<UInputMappingContext*>& MappingContexts,
    const FModifyContextOptions& Options)
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (UInputMappingContext* MappingContext : MappingContexts)
        {
            Subsystem->RemoveMappingContext(MappingContext, Options);
        }
    }
}

void UInputManagerComponent::BindInputAction(const FInputActionConfigData& Config)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetEnhancedInputComponent())
    {
        if (Config.InputAction && !Config.TriggerEvents.IsEmpty())
        {
            for (ETriggerEvent TriggerEvent : Config.TriggerEvents)
            {
                uint32 InputActionBindingHandle;
                switch (TriggerEvent)
                {
                case ETriggerEvent::None:
                    continue;
                    break;
                case ETriggerEvent::Triggered:
                    InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                        Config.InputAction,
                        TriggerEvent,
                        [&](const FInputActionInstance& ActionInstance){ OnInputActionTriggered(ActionInstance); }).GetHandle();
                    break;
                case ETriggerEvent::Started:
                    InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                        Config.InputAction,
                        TriggerEvent,
                        [&](const FInputActionInstance& ActionInstance){ OnInputActionStarted(ActionInstance); }).GetHandle();
                    break;
                case ETriggerEvent::Ongoing:
                    InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                        Config.InputAction,
                        TriggerEvent,
                        [&](const FInputActionInstance& ActionInstance){ OnInputActionOngoing(ActionInstance); }).GetHandle();
                    break;
                case ETriggerEvent::Canceled:
                    InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                        Config.InputAction,
                        TriggerEvent,
                        [&](const FInputActionInstance& ActionInstance){ OnInputActionCanceled(ActionInstance); }).GetHandle();
                    break;
                case ETriggerEvent::Completed:
                    InputActionBindingHandle = EnhancedInputComponent->BindActionInstanceLambda(
                        Config.InputAction,
                        TriggerEvent,
                        [&](const FInputActionInstance& ActionInstance){ OnInputActionCompleted(ActionInstance); }).GetHandle();
                    break;
                }

                InputActionBindingHandles.Emplace(InputActionBindingHandle);
            }
        }
    }
}

void UInputManagerComponent::UnbindInputAction(const FInputActionConfigData& Config)
{
}

APlayerController* UInputManagerComponent::GetPlayerController() const
{
    APlayerController* PlayerController = nullptr;

    if (GetOwner()->IsA<APlayerController>())
    {
        PlayerController = Cast<APlayerController>(GetOwner());
    }
    else if (GetOwner()->IsA<APawn>())
    {
        PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
    }
    else if (GetOwner()->IsA<AGameModeBase>() || GetOwner()->IsA<AGameStateBase>())
    {
        PlayerController = GetWorld()->GetFirstPlayerController();
    }

    return PlayerController;
}

UEnhancedInputLocalPlayerSubsystem* UInputManagerComponent::GetEnhancedInputLocalPlayerSubsystem() const
{
    if (APlayerController* PlayerController = GetPlayerController())
    {
        return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    }

    return nullptr;
}

UEnhancedInputComponent* UInputManagerComponent::GetEnhancedInputComponent() const
{
    if (APlayerController* PlayerController = GetPlayerController())
    {
        return Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
    }

    return nullptr;
}

void UInputManagerComponent::BindInputActions()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetEnhancedInputComponent())
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

void UInputManagerComponent::UnbindInputActions()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetEnhancedInputComponent())
    {
        for (uint32 InputBindingHandle : InputActionBindingHandles)
        {
            EnhancedInputComponent->RemoveActionBindingForHandle(InputBindingHandle);
        }
        InputActionBindingHandles.Reset();
    }
}

void UInputManagerComponent::OnInputActionTriggered_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UInputManagerComponent::OnInputActionStarted_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UInputManagerComponent::OnInputActionOngoing_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UInputManagerComponent::OnInputActionCanceled_Implementation(const FInputActionInstance& InputActionInstance)
{
}

void UInputManagerComponent::OnInputActionCompleted_Implementation(const FInputActionInstance& InputActionInstance)
{
}
