// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputManagerComponent.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UInputManagerComponent::UInputManagerComponent()
{
}

void UInputManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    AddMappingContexts(DefaultMappingContexts);
}

void UInputManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
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

UEnhancedInputLocalPlayerSubsystem* UInputManagerComponent::GetEnhancedInputLocalPlayerSubsystem() const
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

    return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
}
