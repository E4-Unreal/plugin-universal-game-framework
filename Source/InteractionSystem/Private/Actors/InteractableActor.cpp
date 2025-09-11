// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

#include "Components/InteractionSystemComponent.h"

FName AInteractableActor::DefaultSceneName(TEXT("DefaultScene"));
FName AInteractableActor::DisplayMeshName(TEXT("DisplayMesh"));

AInteractableActor::AInteractableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DefaultScene */

    DefaultScene = CreateDefaultSubobject<USceneComponent>(DefaultSceneName);
    SetRootComponent(GetDefaultScene());

    /* DisplayMesh */

    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(DisplayMeshName);
    GetDisplayMesh()->SetupAttachment(GetRootComponent());
}

void AInteractableActor::NotifyActorBeginCursorOver()
{
    Super::NotifyActorBeginCursorOver();

    if (APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn())
    {
        if (auto InteractionSystem = PlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
        {
            InteractionSystem->SelectTarget(this);
        }
    }
}

void AInteractableActor::NotifyActorEndCursorOver()
{
    Super::NotifyActorEndCursorOver();

    if (APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn())
    {
        if (auto InteractionSystem = PlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
        {
            InteractionSystem->DeselectTarget(this);
        }
    }
}

void AInteractableActor::SetFocus_Implementation(AActor* Interactor)
{
    Super::SetFocus_Implementation(Interactor);

    if (Interactor)
    {
        GetDisplayMesh()->SetRenderCustomDepth(true);
    }
}

void AInteractableActor::ClearFocus_Implementation(AActor* Interactor)
{
    Super::ClearFocus_Implementation(Interactor);

    if (Interactor)
    {
        GetDisplayMesh()->SetRenderCustomDepth(false);
    }
}
