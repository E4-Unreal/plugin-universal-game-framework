// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Interfaces/QuickSlotWidgetInterface.h"
#include "QuickSlotWidgetBase.generated.h"

class UQuickSlotManagerComponent;

/**
 *
 */
UCLASS(Abstract)
class QUICKSLOTMANAGER_API UQuickSlotWidgetBase : public UCommonUserWidget, public IQuickSlotWidgetInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UObject> QuickSlotManager;

public:
    /* QuickSlotWidgetInterface */

    virtual void SetQuickSlotManager_Implementation(const TScriptInterface<IQuickSlotManagerInterface>& NewQuickSlotManager) override { QuickSlotManager = NewQuickSlotManager.GetObject(); }

protected:
    virtual void NativeOnInitialized() override;
};
