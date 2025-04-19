// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

#include "Components/SphereComponent.h"

AInteractableActor::AInteractableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer
        .SetDefaultSubobjectClass<UStaticMeshComponent>(DisplayMeshName)
        .SetDefaultSubobjectClass<USphereComponent>(OverlapShapeName)
        )
{
    auto OverlapSphere = GetOverlapShape<USphereComponent>();
    OverlapSphere->InitSphereRadius(128.0f);
}
