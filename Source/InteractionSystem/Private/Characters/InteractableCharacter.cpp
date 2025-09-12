// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InteractableCharacter.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameplayTags/InteractionGameplaytags.h"
#include "Interfaces/InteractionWidgetInterface.h"

FName AInteractableCharacter::WidgetComponentName(TEXT("WidgetComponent"));

AInteractableCharacter::AInteractableCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Config */

    bUseCursorOverEvent = true;
    InteractionType = Interaction::Talk;

    /* WidgetComponent */

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(WidgetComponentName);
    GetWidgetComponent()->SetupAttachment(GetRootComponent());
    GetWidgetComponent()->SetVisibility(false);
    GetWidgetComponent()->SetWidgetSpace(EWidgetSpace::Screen);
    GetWidgetComponent()->SetDrawAtDesiredSize(true);
}

void AInteractableCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GetWidgetComponent())
    {
        if (auto Widget = GetWidgetComponent()->GetWidget())
        {
            if (Widget->Implements<UInteractionWidgetInterface>())
            {
                IInteractionWidgetInterface::Execute_SetInteractionType(Widget, Execute_GetInteractionType(this));
                IInteractionWidgetInterface::Execute_SetInteractionMessage(Widget, Execute_GetInteractionMessage(this));
            }
        }
    }
}

void AInteractableCharacter::NotifyActorBeginCursorOver()
{
    Super::NotifyActorBeginCursorOver();

    if (bUseCursorOverEvent)
    {
        if (APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn())
        {
            if (auto InteractionSystem = PlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
            {
                InteractionSystem->SelectTarget(this, true);
            }
        }
    }
}

void AInteractableCharacter::NotifyActorEndCursorOver()
{
    Super::NotifyActorEndCursorOver();

    if (bUseCursorOverEvent)
    {
        if (APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn())
        {
            if (auto InteractionSystem = PlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
            {
                InteractionSystem->DeselectTarget(this, true);
            }
        }
    }
}

void AInteractableCharacter::SetFocus_Implementation(AActor* Interactor)
{
    Super::SetFocus_Implementation(Interactor);

    if (Interactor)
    {
        GetMesh()->SetRenderCustomDepth(true);
        GetWidgetComponent()->SetVisibility(true);
    }
}

void AInteractableCharacter::ClearFocus_Implementation(AActor* Interactor)
{
    Super::ClearFocus_Implementation(Interactor);

    if (Interactor)
    {
        GetMesh()->SetRenderCustomDepth(false);
        GetWidgetComponent()->SetVisibility(false);
    }
}
