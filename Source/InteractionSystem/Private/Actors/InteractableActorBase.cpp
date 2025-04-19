// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"

#include "Logging.h"
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

void AInteractableActorBase::Destroyed()
{
    for (const auto& [Interactor, Timer] : InteractionTimerMap)
    {
        ClearInteractionTimer(Interactor);
    }

    Super::Destroyed();
}

void AInteractableActorBase::TryInteract_Implementation(AActor* Interactor)
{
    SetInteractionTimer(Interactor);
}

void AInteractableActorBase::CancelInteract_Implementation(AActor* Interactor)
{
    ClearInteractionTimer(Interactor);
}

void AInteractableActorBase::SetInteractionTimer(AActor* Interactor)
{
    ClearInteractionTimer(Interactor);

    if (InteractionTime < 0 || FMath::IsNearlyZero(InteractionTime))
    {
        OnInteract(Interactor);
    }
    else
    {
        FTimerHandle Timer;
        FTimerDelegate TimerDelegate;
        TimerDelegate.BindUObject(this, &ThisClass::OnInteract, Interactor);
        GetWorldTimerManager().SetTimer(Timer, TimerDelegate, InteractionTime, false);

        InteractionTimerMap.Emplace(Interactor, Timer);
    }
}

void AInteractableActorBase::ClearInteractionTimer(AActor* Interactor)
{
    if (InteractionTimerMap.Contains(Interactor))
    {
        GetWorldTimerManager().ClearTimer(InteractionTimerMap[Interactor]);
        InteractionTimerMap.Remove(Interactor);
    }
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

void AInteractableActorBase::OnInteract_Implementation(AActor* Interactor)
{
    LOG_TODO
}

void AInteractableActorBase::OnInteractorBeginOverlap_Implementation(AActor* Interactor, UInteractionSystemComponentBase* InteractionSystem)
{
    InteractionSystem->AddTarget(this);
}

void AInteractableActorBase::OnInteractorEndOverlap_Implementation(AActor* Interactor, UInteractionSystemComponentBase* InteractionSystem)
{
    InteractionSystem->RemoveTarget(this);
}
