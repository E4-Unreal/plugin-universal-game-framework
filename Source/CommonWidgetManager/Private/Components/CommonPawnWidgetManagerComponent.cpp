// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommonPawnWidgetManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/CommonPlayerWidgetManagerComponent.h"
#include "Subsystems/CommonWidgetManagerSubsystem.h"

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
            for (const auto& [InputAction, LayerWidgetClass] : ToggleableLayerWidgetMap)
            {
                EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::ToggleLayerWidget, LayerWidgetClass);
            }
        }
    }
}

void UCommonPawnWidgetManagerComponent::ToggleLayerWidget(TSubclassOf<UCommonLayerWidgetBase> LayerWidgetClass)
{
    if (UCommonWidgetManagerSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCommonWidgetManagerSubsystem>())
    {
        Subsystem->ToggleLayerWidget(GetOwner(), LayerWidgetClass);
    }
}

void UCommonPawnWidgetManagerComponent::ShowHUDWidget(AActor* PlayerActor)
{
    if (UCommonWidgetManagerSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCommonWidgetManagerSubsystem>())
    {
        Subsystem->ShowLayerWidget(PlayerActor, HUDWidgetClass);
    }
}

void UCommonPawnWidgetManagerComponent::HideHUDWidget(AActor* PlayerActor)
{
    if (UCommonWidgetManagerSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCommonWidgetManagerSubsystem>())
    {
        Subsystem->HideLayerWidget(PlayerActor, HUDWidgetClass);
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
