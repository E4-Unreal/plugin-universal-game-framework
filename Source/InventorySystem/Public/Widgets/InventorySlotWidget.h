// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidgetBase.h"
#include "InventorySlotWidget.generated.h"

class UDraggedInventorySlotWidget;
class UTextBlock;
class UImage;
class UInventoryComponent;
struct FInventorySlot;

/**
 *
 */
UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventorySlotWidget : public UInventorySlotWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> QuantityTextBlock;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UInventorySlotWidgetBase> DraggedWidgetClass;

protected:
    /* UserWidget */

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    /* InventorySlotWidgetBase */

    virtual void UpdateInventorySlot(const FInventorySlot& InventorySlot) override;
    virtual void Clear() override;

    /* InventoryWidgetBase */

    UFUNCTION(BlueprintPure)
    virtual UTextBlock* GetQuantityTextBlock() const { return QuantityTextBlock; }

    UFUNCTION(BlueprintCallable)
    virtual void SetQuantityTextBlock(int32 Quantity);
};
