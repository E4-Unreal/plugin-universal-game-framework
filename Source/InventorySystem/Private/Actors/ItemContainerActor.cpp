// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemContainerActor.h"

#include "Components/InteractableComponent.h"
#include "GameplayTags/InventoryGameplayTags.h"
#include "Components/ItemActorComponent.h"

const FName AItemContainerActor::ItemContainerName(TEXT("ItemContainer"));

AItemContainerActor::AItemContainerActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* InteractableComponent */

    GetInteractableComponent()->InteractionType = Interaction::Open::Box;

    /* ItemContainer */

    ItemContainer = CreateDefaultSubobject<UItemContainerComponent>(ItemContainerName);
}

void AItemContainerActor::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    GetItemContainer()->SpawnItems();
}

void AItemContainerActor::SetItemInstances_Implementation(const TArray<UDataInstanceBase*>& NewItemsInstances)
{
    GetItemContainer()->SetItems(NewItemsInstances);
}
