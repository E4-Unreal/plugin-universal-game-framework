// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/QuickSlotManagerWidgetBase.h"
#include "UGFQuickSlotPanelWidget.generated.h"

class UUGFQuickSlotWidget;
class UUniformGridPanel;

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFQuickSlotPanelWidget : public UQuickSlotManagerWidgetBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> QuickSlotPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUGFQuickSlotWidget> SlotWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotColumn = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 PreviewSlotNum = 4;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "State")
    TMap<int32, TObjectPtr<UUGFQuickSlotWidget>> SlotWidgetMap;

protected:
    virtual void NativePreConstruct() override;

    virtual void ClearSlotWidgets();
    virtual void CreateSlotWidgets();
};
