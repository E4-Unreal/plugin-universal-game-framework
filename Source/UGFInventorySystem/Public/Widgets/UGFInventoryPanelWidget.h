// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGFInventoryPanelWidget.generated.h"

class UUniformGridPanel;
class UUGFInventoryComponent;
class UUGFInventorySlotWidget;

/**
 *
 */
UCLASS(Abstract)
class UGFINVENTORYSYSTEM_API UUGFInventoryPanelWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> InventoryPanel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UUGFInventorySlotWidget> SlotWidgetClass;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "State")
    TMap<int32, TObjectPtr<UUGFInventorySlotWidget>> SlotWidgets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 PreviewSlotNum = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotRow = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotColumn = 1;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "State")
    TObjectPtr<UUGFInventoryComponent> InventoryComponent;

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;

    UFUNCTION(BlueprintCallable)
    virtual void CreateSlotWidgets();

    UFUNCTION(BlueprintCallable)
    virtual void OnInventoryUpdated(int32 SlotIndex);
};
