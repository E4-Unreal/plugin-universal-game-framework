// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"

#include "Components/InteractionWidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

FName AInteractableActor::DefaultSceneName(TEXT("DefaultScene"));
FName AInteractableActor::DisplayMeshName(TEXT("DisplayMesh"));
FName AInteractableActor::WidgetComponentName(TEXT("WidgetComponent"));
FName AInteractableActor::OverlapSphereName(TEXT("OverlapSphere"));

AInteractableActor::AInteractableActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer
        .SetDefaultSubobjectClass(WidgetComponentName, UInteractionWidgetComponent::StaticClass()))
{
    /* DefaultScene */

    DefaultScene = CreateDefaultSubobject<USceneComponent>(DefaultSceneName);
    SetRootComponent(GetDefaultScene());

    /* DisplayMesh */

    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(DisplayMeshName);
    GetDisplayMesh()->SetupAttachment(GetRootComponent());

    /* WidgetComponent */

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(WidgetComponentName);
    GetWidgetComponent()->SetupAttachment(GetRootComponent());

    /* OverlapSphere */

    OverlapSphere = CreateDefaultSubobject<USphereComponent>(OverlapSphereName);
    GetOverlapSphere()->SetupAttachment(GetRootComponent());
    GetOverlapSphere()->SetSphereRadius(128.0f);
}
