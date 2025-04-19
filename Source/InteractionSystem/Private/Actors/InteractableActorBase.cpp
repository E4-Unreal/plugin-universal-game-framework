// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"

#include "Components/InteractableComponent.h"
#include "Components/SphereComponent.h"

FName AInteractableActorBase::DisplayMeshName(TEXT("DisplayMesh"));
FName AInteractableActorBase::OverlapShapeName(TEXT("OverlapShape"));
FName AInteractableActorBase::InteractableComponentName(TEXT("InteractableComponent"));

AInteractableActorBase::AInteractableActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UMeshComponent>(DisplayMeshName);
    if (DisplayMesh) SetRootComponent(DisplayMesh);

    /* OverlapShape */
    OverlapShape = CreateDefaultSubobject<UShapeComponent>(OverlapShapeName);
    if (OverlapShape) OverlapShape->SetupAttachment(RootComponent);

    /* InteractableComponent */
    InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(InteractableComponentName);
    if (OverlapShape) InteractableComponent->SetOverlapShape(OverlapShape);
}

void AInteractableActorBase::BeginPlay()
{
    Super::BeginPlay();

    InteractableComponent->OnInteractionTriggered.AddDynamic(this, &ThisClass::OnInteractionTriggered);
}

bool AInteractableActorBase::CanInteract_Implementation(AActor* Interactor)
{
    return Execute_CanInteract(InteractableComponent, Interactor);
}

void AInteractableActorBase::TryInteract_Implementation(AActor* Interactor)
{
    Execute_TryInteract(InteractableComponent, Interactor);
}

void AInteractableActorBase::CancelInteract_Implementation(AActor* Interactor)
{
    Execute_CancelInteract(InteractableComponent, Interactor);
}

void AInteractableActorBase::OnInteractionTriggered_Implementation(AActor* Interactor)
{

}
