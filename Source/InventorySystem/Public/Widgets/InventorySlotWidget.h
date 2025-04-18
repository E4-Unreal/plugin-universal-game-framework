// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
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
class INVENTORYSYSTEM_API UInventorySlotWidget : public UInventoryWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> QuantityTextBlock;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UDraggedInventorySlotWidget> DraggedWidgetClass;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "State")
    int32 Index;

public:
    UFUNCTION(BlueprintCallable)
    void SetIndex(int32 NewIndex) { Index = NewIndex; }

    UFUNCTION(BlueprintCallable)
    virtual void Clear();

    /* InventoryWidgetBase */

    virtual void Refresh() override;

protected:
    /* UserWidget */

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    /* InventoryWidgetBase */

    UFUNCTION(BlueprintPure)
    virtual UImage* GetThumbnailImage() const { return ThumbnailImage; }

    UFUNCTION(BlueprintPure)
    virtual UTextBlock* GetQuantityTextBlock() const { return QuantityTextBlock; }

    UFUNCTION(BlueprintCallable)
    virtual void FetchInventorySlot(const FInventorySlot& InventorySlot);

    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture);

    UFUNCTION(BlueprintCallable)
    virtual void SetQuantityTextBlock(int32 Quantity);
};
