// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StorageActor.h"

#include "Components/InventoryComponent.h"

const FName AStorageActor::InventoryName(TEXT("Inventory"));

AStorageActor::AStorageActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Inventory */
    Inventory = CreateDefaultSubobject<UInventoryComponent>(InventoryName);
    Inventory->MaxSlotNum = 10;
}
