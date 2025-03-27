// Fill out your copyright notice in the Description page of Project Settings.


#include "Componenets/UGFInputComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/UGFInputConfig.h"

APawn* UUGFInputComponent::GetOwningPawn() const
{
    if (AActor* Owner = GetOwner())
    {
        return Cast<APawn>(Owner);
    }

    return nullptr;
}

APlayerController* UUGFInputComponent::GetOwningPlayer() const
{
    if (APawn* Pawn = GetOwningPawn())
    {
        if (AController* Controller = Pawn->GetController())
        {
            return Cast<APlayerController>(Controller);
        }
    }

    return nullptr;
}

UEnhancedInputComponent* UUGFInputComponent::GetEnhancedInputComponent() const
{
    if (APawn* OwningPawn = GetOwningPawn())
    {
        if (OwningPawn->InputComponent)
        {
            return Cast<UEnhancedInputComponent>(OwningPawn->InputComponent);
        }
    }

    return nullptr;
}

UEnhancedInputLocalPlayerSubsystem* UUGFInputComponent::GetEnhancedInputLocalPlayerSubsystem() const
{
    if (APlayerController* PlayerController = GetOwningPlayer())
    {
        return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    }

    return nullptr;
}

void UUGFInputComponent::BindEnhancedInput()
{
    BindInputConfigs();

    AddMappingContexts();
}

void UUGFInputComponent::BindInputConfigs()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetEnhancedInputComponent())
    {
        for (const auto& InputConfig : InputConfigs)
        {
            if(InputConfig)
            {
                InputConfig->BindEnhancedInput(EnhancedInputComponent);
            }
        }
    }
}

void UUGFInputComponent::AddMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (const auto& InputMappingContextData : InputMappingContextDataList)
        {
            if (!Subsystem->HasMappingContext(InputMappingContextData.InputMappingContext))
            {
                Subsystem->AddMappingContext(InputMappingContextData.InputMappingContext, InputMappingContextData.Priority);
            }
        }
    }
}
