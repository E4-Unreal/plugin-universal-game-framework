// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StorageWidget.h"

#include "Components/InventoryComponent.h"
#include "Widgets/InventoryPanelWidget.h"

void UStorageWidget::SetTargetActor(AActor* NewTargetActor)
{
    if (TargetActor != NewTargetActor)
    {
        OnTargetActorChanged(TargetActor, NewTargetActor);
        TargetActor = NewTargetActor;
    }
}

void UStorageWidget::OnTargetActorChanged(AActor* OldTargetActor, AActor* NewTargetActor)
{
    GetStoragePanel()->SetInventoryComponent(NewTargetActor->GetComponentByClass<UInventoryComponent>());
}
