// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "InventorySlotWidgetBase.generated.h"

struct FInventorySlot;
class UImage;

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySlotWidgetBase : public UInventoryWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "State")
    int32 SlotIndex;

public:
    UFUNCTION(BlueprintCallable)
    void SetSlotIndex(int32 NewSlotIndex);

    UFUNCTION(BlueprintPure)
    int32 GetSlotIndex() const { return SlotIndex; }

public:
    /* InventoryWidgetBase */

    virtual void Refresh() override;

protected:
    /* InventorySlotWidgetBase */

    UFUNCTION(BlueprintCallable)
    virtual void UpdateInventorySlot(const FInventorySlot& InventorySlot);

    UFUNCTION(BlueprintCallable)
    virtual void Clear();

    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture);

    UFUNCTION(BlueprintPure)
    virtual UImage* GetThumbnailImage() const { return ThumbnailImage; }
};
