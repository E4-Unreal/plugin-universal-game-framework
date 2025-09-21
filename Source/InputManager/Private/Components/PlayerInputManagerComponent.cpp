// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerInputManagerComponent.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


UPlayerInputManagerComponent::UPlayerInputManagerComponent()
{
}

void UPlayerInputManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    AddDefaultMappingContexts();
}

void UPlayerInputManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    RemoveDefaultMappingContexts();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

UEnhancedInputLocalPlayerSubsystem* UPlayerInputManagerComponent::GetEnhancedInputLocalPlayerSubsystem() const
{
    return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CastChecked<APlayerController>(GetOwner())->GetLocalPlayer());
}

void UPlayerInputManagerComponent::AddDefaultMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (UInputMappingContext* DefaultMappingContext : DefaultMappingContexts)
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void UPlayerInputManagerComponent::RemoveDefaultMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (UInputMappingContext* DefaultMappingContext : DefaultMappingContexts)
        {
            Subsystem->RemoveMappingContext(DefaultMappingContext);
        }
    }
}
