// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFNonPlayerCharacter.h"

#include "Subsystems/CommonWidgetManagerSubsystem.h"


AUGFNonPlayerCharacter::AUGFNonPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

bool AUGFNonPlayerCharacter::CanInteract_Implementation(AActor* Interactor)
{
    if (APawn* Pawn = Cast<APawn>(Interactor))
    {
        return Pawn->IsPlayerControlled() && Pawn->IsLocallyControlled();
    }

    return false;
}

void AUGFNonPlayerCharacter::Interact_Implementation(AActor* Interactor)
{
    if (!Execute_CanInteract(this, Interactor)) return;

    if (UCommonWidgetManagerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCommonWidgetManagerSubsystem>())
    {
        Subsystem->ShowLayerWidget(Interactor, MenuWidgetClass);
    }
}

void AUGFNonPlayerCharacter::CancelInteract_Implementation(AActor* Interactor)
{
}
