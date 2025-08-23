// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SlotWidgetBase.h"
#include "QuickSlotWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class QUICKSLOTMANAGER_API UQuickSlotWidget : public USlotWidgetBase
{
    GENERATED_BODY()

public:
    UQuickSlotWidget(const FObjectInitializer& ObjectInitializer);
};
