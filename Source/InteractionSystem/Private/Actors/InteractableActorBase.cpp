// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"

#include "Components/InteractionSystemComponentBase.h"
#include "Components/SphereComponent.h"

FName AInteractableActorBase::DisplayMeshName(TEXT("DisplayMesh"));
FName AInteractableActorBase::OverlapShapeName(TEXT("OverlapShape"));

AInteractableActorBase::AInteractableActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UMeshComponent>(DisplayMeshName);
    if (DisplayMesh)
    {
        SetRootComponent(DisplayMesh);
    }

    /* OverlapShape */
    OverlapShape = CreateDefaultSubobject<UShapeComponent>(OverlapShapeName);
    if (OverlapShape)
    {
        OverlapShape->SetupAttachment(RootComponent);
    }
}

void AInteractableActorBase::BeginPlay()
{
    Super::BeginPlay();

    OverlapShape->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeBeginOverlap);
    OverlapShape->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeEndOverlap);
}

void AInteractableActorBase::OnOverlapShapeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (auto InteractionSystem = OtherActor->GetComponentByClass<UInteractionSystemComponentBase>())
    {
        OnInteractorBeginOverlap(OtherActor, InteractionSystem);
    }
}

void AInteractableActorBase::OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (auto InteractionSystem = OtherActor->GetComponentByClass<UInteractionSystemComponentBase>())
    {
        OnInteractorEndOverlap(OtherActor, InteractionSystem);
    }
}

void AInteractableActorBase::OnInteractorBeginOverlap_Implementation(AActor* Interactor, UInteractionSystemComponentBase* InteractionSystem)
{
    InteractionSystem->AddTarget(this);
}

void AInteractableActorBase::OnInteractorEndOverlap_Implementation(AActor* Interactor, UInteractionSystemComponentBase* InteractionSystem)
{
    InteractionSystem->RemoveTarget(this);
}
