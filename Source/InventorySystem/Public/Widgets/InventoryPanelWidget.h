// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "InventoryPanelWidget.generated.h"

class UUniformGridPanel;
class UInventorySlotWidget;

/**
 *
 */
UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventoryPanelWidget : public UInventoryWidgetBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> InventoryPanel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UInventorySlotWidget> SlotWidgetClass;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "State")
    TMap<int32, TObjectPtr<UInventorySlotWidget>> SlotWidgets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 PreviewSlotNum = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotRow = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotColumn = 1;

protected:
    virtual void NativePreConstruct() override;

    virtual void OnInventoryComponentChanged(UInventoryComponent* OldInventoryComponent, UInventoryComponent* NewInventoryComponent) override;

    UFUNCTION(BlueprintCallable)
    virtual void CreateSlotWidgets();

    UFUNCTION(BlueprintCallable)
    virtual void OnInventoryUpdated(int32 SlotIndex);
};
