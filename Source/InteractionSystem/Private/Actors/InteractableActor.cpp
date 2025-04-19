// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

#include "Components/SphereComponent.h"

AInteractableActor::AInteractableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer
        .SetDefaultSubobjectClass<UStaticMeshComponent>(DisplayMeshName)
        .SetDefaultSubobjectClass<USphereComponent>(OverlapShapeName)
        )
{
    /* DisplayStaticMesh */
    auto DisplayStaticMesh = GetDisplayStaticMesh();
    ConstructorHelpers::FObjectFinder<UStaticMesh> DisplayMeshFinder(TEXT("/Engine/BasicShapes/Cube"));
    if (DisplayMeshFinder.Succeeded()) DisplayStaticMesh->SetStaticMesh(DisplayMeshFinder.Object);
    ConstructorHelpers::FObjectFinder<UMaterial> DisplayMeshMaterialFinder(TEXT("/Engine/BasicShapes/BasicShapeMaterial"));
    if (DisplayMeshMaterialFinder.Succeeded()) DisplayStaticMesh->SetMaterial(0, DisplayMeshMaterialFinder.Object);

    /* OverlapSphere */
    auto OverlapSphere = GetOverlapSphere();
    OverlapSphere->InitSphereRadius(128.0f);
}
