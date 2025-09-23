// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemDropActor.h"

#include "Components/InteractableComponent.h"
#include "Components/ItemDropComponent.h"
#include "GameplayTags/InteractionGameplayTags.h"

const FName AItemDropActor::ItemDropComponentName(TEXT("ItemDropComponent"));

AItemDropActor::AItemDropActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* InteractableComponent */

    GetInteractableComponent()->InteractionType = Interaction::Open;

    /* ItemContainer */

    ItemDropComponent = CreateDefaultSubobject<UItemDropComponent>(ItemDropComponentName);
}

void AItemDropActor::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    GetItemDropContainer()->DropItems();
}
