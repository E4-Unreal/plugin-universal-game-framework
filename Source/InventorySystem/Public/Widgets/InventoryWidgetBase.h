// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "InventoryWidgetBase.generated.h"

class UInventoryComponent;
class UInventorySlotWidgetBase;

UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventoryWidgetBase : public UCommonUserWidget
{
    GENERATED_BODY()

private:
    TWeakObjectPtr<UInventoryComponent> InventoryComponentPrivate;

public:
    UFUNCTION(BlueprintCallable)
    virtual void Refresh() {}

protected:
    /* UserWidget */

    virtual void NativeOnInitialized() override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    /* InventoryWidgetBase */

    virtual void FindInventoryComponent();

    void FindInventoryComponentFromParentWidget();

    void FindInventoryComponentFromPlayer();

    void FindInventoryComponentFromPlayerPawn();

    virtual void OnInventoryComponentChanged(UInventoryComponent* OldInventoryComponent, UInventoryComponent* NewInventoryComponent) {}

    virtual void OnInventorySlotWidgetDrop(UInventorySlotWidgetBase* InventorySlotWidget) {}

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponentPrivate.Get(); }

    UFUNCTION(BlueprintCallable)
    void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);
};
