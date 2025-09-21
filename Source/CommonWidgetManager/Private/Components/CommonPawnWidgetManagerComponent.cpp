// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommonPawnWidgetManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/CommonPlayerWidgetManagerComponent.h"
#include "Subsystems/WidgetManagerSubsystem.h"

void UCommonPawnWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    ShowHUDWidget(GetOwner());

    BindEvents();
}

void UCommonPawnWidgetManagerComponent::BindEvents()
{
    if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
    {
        OwningPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &ThisClass::OnControllerChanged);

        if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwningPawn->InputComponent))
        {
            for (const auto& [InputAction, LayerWidgetClass] : ToggleableWidgetMap)
            {
                EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::ToggleWidget, LayerWidgetClass);
            }
        }
    }
}

void UCommonPawnWidgetManagerComponent::ToggleWidget(TSubclassOf<UUserWidget> LayerWidgetClass)
{
    if (auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        Subsystem->ToggleWidget(GetOwner(), LayerWidgetClass);
    }
}

void UCommonPawnWidgetManagerComponent::ShowHUDWidget(AActor* PlayerActor)
{
    if (auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        Subsystem->ShowWidget(PlayerActor, HUDWidgetClass);
    }
}

void UCommonPawnWidgetManagerComponent::HideHUDWidget(AActor* PlayerActor)
{
    if (auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        Subsystem->HideWidget(PlayerActor, HUDWidgetClass);
    }
}

void UCommonPawnWidgetManagerComponent::OnControllerChanged(APawn* Pawn, AController* OldController,
                                                            AController* NewController)
{
    if (OldController)
    {
        HideHUDWidget(OldController);
    }

    if (NewController)
    {
        ShowHUDWidget(NewController);
    }
}
