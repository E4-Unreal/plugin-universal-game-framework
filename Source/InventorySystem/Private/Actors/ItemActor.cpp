// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActor.h"

#include "Components/InteractableComponent.h"
#include "GameplayTags/InteractionGameplayTags.h"
#include "Components/ItemComponent.h"

const FName AItemActor::ItemComponentName(TEXT("ItemComponent"));

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */

    GetDisplayMesh()->SetSimulatePhysics(true);

    /* InteractableComponent */

    GetInteractableComponent()->InteractionType = Interaction::Pickup;

    /* ItemComponent */

    ItemComponent = CreateDefaultSubobject<UItemComponent>(ItemComponentName);
}

void AItemActor::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    GetItemComponent()->AddItemsToInventory(Interactor);
}

void AItemActor::SetItemInstances_Implementation(const TArray<UDataInstanceBase*>& NewItemsInstances)
{
    GetItemComponent()->SetItems(NewItemsInstances);
    GetInteractableComponent()->SetInteractionMessage(GetItemComponent()->GetItemName());
}
