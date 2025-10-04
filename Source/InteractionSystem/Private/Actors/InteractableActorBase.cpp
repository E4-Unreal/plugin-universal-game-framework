// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActorBase.h"

#include "Components/InteractableComponent.h"

FName AInteractableActorBase::InteractableComponentName(TEXT("InteractableComponent"));

AInteractableActorBase::AInteractableActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* InteractableComponent */

    InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(InteractableComponentName);
}
