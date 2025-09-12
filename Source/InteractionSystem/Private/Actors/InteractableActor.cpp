// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameplayTags/InteractionGameplaytags.h"
#include "Interfaces/InteractionWidgetInterface.h"

FName AInteractableActor::DefaultSceneName(TEXT("DefaultScene"));
FName AInteractableActor::DisplayMeshName(TEXT("DisplayMesh"));
FName AInteractableActor::WidgetComponentName(TEXT("WidgetComponent"));

AInteractableActor::AInteractableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Config */

    bUseCursorOverEvent = true;
    InteractionType = Interaction::Root;

    /* DefaultScene */

    DefaultScene = CreateDefaultSubobject<USceneComponent>(DefaultSceneName);
    SetRootComponent(GetDefaultScene());

    /* DisplayMesh */

    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(DisplayMeshName);
    GetDisplayMesh()->SetupAttachment(GetRootComponent());

    /* WidgetComponent */

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(WidgetComponentName);
    GetWidgetComponent()->SetupAttachment(GetRootComponent());
    GetWidgetComponent()->SetVisibility(false);
    GetWidgetComponent()->SetWidgetSpace(EWidgetSpace::Screen);
    GetWidgetComponent()->SetDrawAtDesiredSize(true);
}

void AInteractableActor::BeginPlay()
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

void AInteractableActor::NotifyActorBeginCursorOver()
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

void AInteractableActor::NotifyActorEndCursorOver()
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

void AInteractableActor::SetFocus_Implementation(AActor* Interactor)
{
    Super::SetFocus_Implementation(Interactor);

    if (Interactor)
    {
        GetDisplayMesh()->SetRenderCustomDepth(true);
        GetWidgetComponent()->SetVisibility(true);
    }
}

void AInteractableActor::ClearFocus_Implementation(AActor* Interactor)
{
    Super::ClearFocus_Implementation(Interactor);

    if (Interactor)
    {
        GetDisplayMesh()->SetRenderCustomDepth(false);
        GetWidgetComponent()->SetVisibility(false);
    }
}
