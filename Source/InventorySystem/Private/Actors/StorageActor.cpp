// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StorageActor.h"

#include "Components/InteractableComponent.h"
#include "Components/InventoryComponent.h"
#include "GameplayTags/InteractionGameplayTags.h"

const FName AStorageActor::InventoryName(TEXT("Inventory"));

AStorageActor::AStorageActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Inventory */

    Inventory = CreateDefaultSubobject<UInventoryComponent>(InventoryName);
    GetInventory()->MaxSlotNum = 10;

    /* InteractableComponent */

    GetInteractableComponent()->InteractionType = Interaction::Open;
    GetInteractableComponent()->InteractionMessage = NSLOCTEXT("InventorySystem", "Storage", "Storage");
}
