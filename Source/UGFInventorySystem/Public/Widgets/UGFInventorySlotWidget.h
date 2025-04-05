// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/UGFInventorySlot.h"
#include "UGFInventorySlotWidget.generated.h"

class UUGFDraggedInventorySlotWidget;
class UTextBlock;
class UImage;
class UUGFInventoryComponent;

/**
 *
 */
UCLASS(Abstract)
class UGFINVENTORYSYSTEM_API UUGFInventorySlotWidget : public UUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> QuantityTextBlock;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UUGFDraggedInventorySlotWidget> DraggedWidgetClass;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "State")
    int32 Index;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "State")
    TObjectPtr<UUGFInventoryComponent> InventoryComponent;

public:
    UFUNCTION(BlueprintCallable)
    void InitializeInventorySlot(UUGFInventoryComponent* InInventoryComponent, int32 InIndex);

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

    UFUNCTION(BlueprintCallable)
    virtual void Clear();

protected:
    /* UserWidget */

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UFUNCTION(BlueprintPure)
    virtual UImage* GetThumbnailImage() const { return ThumbnailImage; }

    UFUNCTION(BlueprintPure)
    virtual UTextBlock* GetQuantityTextBlock() const { return QuantityTextBlock; }

    UFUNCTION(BlueprintCallable)
    virtual void SetInventorySlot(const FUGFInventorySlot& InInventorySlot);

    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture);

    UFUNCTION(BlueprintCallable)
    virtual void SetQuantityTextBlock(int32 Quantity);
};
