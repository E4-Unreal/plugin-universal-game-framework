// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLayoutWidgetBase.h"
#include "CommonLayoutWidget.generated.h"

class UCommonActivatableWidget;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonLayoutWidget : public UCommonLayoutWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> GameOverlayLayer;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> GameMenuLayer;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> SystemPopupLayer;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> SystemMenuLayer;

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;

    virtual void SetLayers();

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonActivatableWidgetStack* GetGameOverlayLayer() const { return GameOverlayLayer; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonActivatableWidgetStack* GetGameMenuLayer() const { return GameMenuLayer; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonActivatableWidgetStack* GetSystemPopupLayer() const { return SystemPopupLayer; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonActivatableWidgetStack* GetSystemMenuLayer() const { return SystemMenuLayer; }
};
