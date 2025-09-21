// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StorageActor.h"

#include "Blueprint/UserWidget.h"
#include "Components/InventoryComponent.h"
#include "Interfaces/TargetWidgetInterface.h"
#include "Subsystems/WidgetManagerSubsystem.h"

const FName AStorageActor::InventoryName(TEXT("Inventory"));

AStorageActor::AStorageActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Inventory */
    Inventory = CreateDefaultSubobject<UInventoryComponent>(InventoryName);
    GetInventory()->MaxSlotNum = 10;
}

void AStorageActor::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    if (auto Subsystem = GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        UUserWidget* Widget = Subsystem->ShowWidget(Interactor, StorageWidgetClass);
        if (Widget && Widget->Implements<UTargetWidgetInterface>())
        {
            ITargetWidgetInterface::Execute_SetTargetActor(Widget, this);
        }
    }
}
