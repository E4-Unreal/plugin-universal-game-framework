// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InteractableCharacter.h"

#include "Components/InteractableComponent.h"
#include "Components/InteractionWidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

FName AInteractableCharacter::WidgetComponentName(TEXT("WidgetComponent"));
FName AInteractableCharacter::OverlapSphereName(TEXT("OverlapSphere"));

AInteractableCharacter::AInteractableCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer
        .SetDefaultSubobjectClass(WidgetComponentName, UInteractionWidgetComponent::StaticClass()))
{
    /* WidgetComponent */

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(WidgetComponentName);
    GetWidgetComponent()->SetupAttachment(GetRootComponent());

    /* OverlapSphere */

    OverlapSphere = CreateDefaultSubobject<USphereComponent>(OverlapSphereName);
    GetOverlapSphere()->SetupAttachment(GetRootComponent());
}

void AInteractableCharacter::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    if (GetInteractableComponent())
    {
        GetInteractableComponent()->SetOverlapShape(GetOverlapSphere());
    }
}
