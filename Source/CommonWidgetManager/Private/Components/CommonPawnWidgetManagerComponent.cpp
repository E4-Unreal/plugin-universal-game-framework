// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommonPawnWidgetManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/CommonPlayerWidgetManagerComponent.h"

void UCommonPawnWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    ShowHUDWidget();
    BindEvents();
    BindActions();
}

void UCommonPawnWidgetManagerComponent::BindEvents()
{
    APawn* OwningPawn = GetOwningPawn();

    OwningPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &ThisClass::OnControllerChanged);
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

void UCommonPawnWidgetManagerComponent::ShowHUDWidget()
{
    APawn* OwningPawn = GetOwningPawn();
    AController* OwningController = OwningPawn->GetController();

    if (OwningController && OwningController->IsLocalPlayerController())
    {
        if (UCommonPlayerWidgetManagerComponent* WidgetManager = OwningController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>())
        {
            WidgetManager->ShowLayerWidget(HUDWidgetClass);
        }
    }
}

void UCommonPawnWidgetManagerComponent::HideHUDWidget()
{
    APawn* OwningPawn = GetOwningPawn();
    AController* OwningController = OwningPawn->GetController();

    if (OwningController && OwningController->IsLocalPlayerController())
    {
        if (UCommonPlayerWidgetManagerComponent* WidgetManager = OwningController->GetComponentByClass<UCommonPlayerWidgetManagerComponent>())
        {
            WidgetManager->HideLayerWidget(HUDWidgetClass);
        }
    }
}

void UCommonPawnWidgetManagerComponent::OnControllerChanged(APawn* Pawn, AController* OldController,
    AController* NewController)
{
    if (OldController)
    {
        HideHUDWidget();
    }

    if (NewController)
    {
        ShowHUDWidget();
    }
}
