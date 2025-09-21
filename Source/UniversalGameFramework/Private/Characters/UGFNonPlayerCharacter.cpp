// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFNonPlayerCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Interfaces/TargetWidgetInterface.h"
#include "Subsystems/WidgetManagerSubsystem.h"


AUGFNonPlayerCharacter::AUGFNonPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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

    if (auto Subsystem = GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        UUserWidget* MenuWidget = Subsystem->ShowWidget(Interactor, MenuWidgetClass);
        if (MenuWidget && MenuWidget->Implements<UTargetWidgetInterface>())
        {
            ITargetWidgetInterface::Execute_SetTargetActor(MenuWidget, this);
        }
    }
}

void AUGFNonPlayerCharacter::CancelInteract_Implementation(AActor* Interactor)
{
}
