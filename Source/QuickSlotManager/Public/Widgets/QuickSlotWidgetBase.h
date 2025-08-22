// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "QuickSlotWidgetBase.generated.h"

class UQuickSlotManagerComponent;

/**
 *
 */
UCLASS(Abstract)
class QUICKSLOTMANAGER_API UQuickSlotWidgetBase : public UCommonUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UQuickSlotManagerComponent> QuickSlotManager;

protected:
    virtual void NativeOnInitialized() override;
};
