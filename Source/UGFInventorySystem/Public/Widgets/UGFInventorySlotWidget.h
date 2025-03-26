// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/UGFInventorySlot.h"
#include "UGFInventorySlotWidget.generated.h"

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
    FUGFInventorySlot DefaultInventorySlot;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "State")
    int32 Index;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Transient, Category = "State")
    TObjectPtr<UUGFInventoryComponent> InventoryComponent;

public:
    UFUNCTION(BlueprintCallable)
    void InitializeInventorySlot(UUGFInventoryComponent* InInventoryComponent, int32 InIndex);

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

protected:
    UFUNCTION(BlueprintCallable)
    virtual void SetInventorySlot(const FUGFInventorySlot& InInventorySlot);
};
