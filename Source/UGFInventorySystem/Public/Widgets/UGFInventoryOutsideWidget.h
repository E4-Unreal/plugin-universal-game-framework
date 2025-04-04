// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGFInventoryOutsideWidget.generated.h"

class UUGFInventoryComponent;

/**
 *
 */
UCLASS()
class UGFINVENTORYSYSTEM_API UUGFInventoryOutsideWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(Transient)
    TObjectPtr<UUGFInventoryComponent> InventoryComponent;

protected:
    virtual void NativeOnInitialized() override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
