// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidgetBase.h"
#include "InventorySlotWidget.generated.h"

class UTextBlock;
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

public:
    /* SlotWidgetInterface */

    virtual void Refresh_Implementation() override;

protected:
    /* SlotWidgetBase */

    virtual void Clear() override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual UTextBlock* GetQuantityTextBlock() const { return QuantityTextBlock; }

    UFUNCTION(BlueprintCallable)
    virtual void SetQuantityTextBlock(int32 Quantity);
};
