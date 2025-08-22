// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/QuickSlotWidgetBase.h"
#include "QuickSlotPanelWidget.generated.h"

class UQuickSlotWidget;
class UUniformGridPanel;

/**
 *
 */
UCLASS()
class QUICKSLOTMANAGER_API UQuickSlotPanelWidget : public UQuickSlotWidgetBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> QuickSlotPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UQuickSlotWidget> SlotWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotColumn = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 PreviewSlotNum = 4;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "State")
    TMap<int32, TObjectPtr<UQuickSlotWidget>> SlotWidgetMap;

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;

    virtual void ClearSlotWidgets();
    virtual void CreateSlotWidgets();

    UFUNCTION()
    virtual void OnSlotIndexChanged(int32 OldSlotIndex, int32 NewSlotIndex);

    UFUNCTION()
    virtual void OnSlotUpdated(int32 SlotIndex);
};
