// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommonPawnWidgetManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/CommonPlayerWidgetManagerComponent.h"

void UCommonPawnWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    BindActions();
}

void UCommonPawnWidgetManagerComponent::BindActions()
{
    APawn* OwningPawn = GetOwningPawn();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwningPawn->InputComponent))
    {
        for (const auto& [InputAction, LayerWidgetClass] : ToggleableLayerWidgetMap)
        {
            EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::ToggleLayerWidget, LayerWidgetClass);
        }
    }
}

void UCommonPawnWidgetManagerComponent::ToggleLayerWidget(TSubclassOf<UCommonLayerWidgetBase> LayerWidgetClass)
{
    APawn* OwningPawn = GetOwningPawn();
    AController* OwningController = OwningPawn->GetController();

    if (OwningController && OwningController->IsLocalPlayerController())
    {
        if (UCommonPlayerWidgetManagerComponent* WidgetManager = OwningController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>())
        {
            WidgetManager->ToggleLayerWidget(LayerWidgetClass);
        }
    }
}
