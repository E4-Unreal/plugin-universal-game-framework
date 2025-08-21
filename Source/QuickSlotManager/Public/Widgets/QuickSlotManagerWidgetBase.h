// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "QuickSlotManagerWidgetBase.generated.h"

class UQuickSlotManagerComponent;

/**
 *
 */
UCLASS(Abstract)
class QUICKSLOTMANAGER_API UQuickSlotManagerWidgetBase : public UCommonUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UQuickSlotManagerComponent> QuickSlotManager;

protected:
    virtual void NativeOnInitialized() override;
};
