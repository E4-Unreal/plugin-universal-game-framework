// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_Interact.h"

#include "Components/InteractionSystemComponentBase.h"

void UInputConfig_Interact::OnStarted_Implementation(APlayerController* PlayerController,
    const FInputActionInstance& InputActionInstance)
{
    Super::OnStarted_Implementation(PlayerController, InputActionInstance);

    if (PlayerController->GetPawn())
    {
        TryInteract(PlayerController->GetPawn());
    }
}

void UInputConfig_Interact::OnCompleted_Implementation(APlayerController* PlayerController,
    const FInputActionInstance& InputActionInstance)
{
    Super::OnCompleted_Implementation(PlayerController, InputActionInstance);

    if (PlayerController->GetPawn())
    {
        CancelInteract(PlayerController->GetPawn());
    }
}

void UInputConfig_Interact::TryInteract(APawn* Pawn)
{
    if (auto InteractionSystem = Pawn->FindComponentByClass<UInteractionSystemComponentBase>())
    {
        InteractionSystem->TryInteract();
    }
}

void UInputConfig_Interact::CancelInteract(APawn* Pawn)
{
    if (auto InteractionSystem = Pawn->FindComponentByClass<UInteractionSystemComponentBase>())
    {
        InteractionSystem->CancelInteract();
    }
}
