// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_Interact.h"

#include "EnhancedInputComponent.h"
#include "Components/InteractionSystemComponentBase.h"

TArray<uint32> UInputConfig_Interact::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    TArray<uint32> InputBindingHandles;
    auto OwningPawn = GetOwningPawn(EnhancedInputComponent);
    if (OwningPawn == nullptr) return InputBindingHandles;

    FEnhancedInputActionEventBinding& TryInteractBinding = EnhancedInputComponent->BindAction(
                InteractAction,
                ETriggerEvent::Started,
                this,
                &ThisClass::TryInteract,
                OwningPawn
                );

    InputBindingHandles.Emplace(TryInteractBinding.GetHandle());

    FEnhancedInputActionEventBinding& CancelInteractBinding = EnhancedInputComponent->BindAction(
               InteractAction,
               ETriggerEvent::Canceled,
               this,
               &ThisClass::CancelInteract,
               OwningPawn
               );

    InputBindingHandles.Emplace(CancelInteractBinding.GetHandle());

    return InputBindingHandles;
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
