// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "Interfaces/LayoutWidgetInterface.h"
#include "Types/LayerConfig.h"
#include "CommonLayoutWidgetBase.generated.h"

class UCommonLayerWidgetBase;
class UCommonActivatableWidget;
class UCommonActivatableWidgetStack;
class ULayerStack;
class UOverlay;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonLayoutWidgetBase : public UCommonActivatableWidget, public ILayoutWidgetInterface
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UOverlay> RootOverlay;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FUIInputConfig UIInputConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> EscapeMenuWidgetClass;

    // TMap<LayerTag, bIsOverlay>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, FLayerConfig> LayerConfigs;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, TObjectPtr<ULayerStack>> LayerMap;

public:
    UCommonLayoutWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* UserWidget */

    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;

    /* CommonActivatableWidget */

    virtual bool NativeOnHandleBackAction() override;
    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

    /* LayoutWidgetInterface */

    virtual UUserWidget* ShowWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass) override;
    virtual bool HideWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass) override;
    virtual void ToggleWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass) override;
    virtual void ExecuteBackAction_Implementation() override;

    /* API */

    UFUNCTION(BlueprintPure, meta = (Categories = "UI.Layer"))
    FORCEINLINE ULayerStack* GetLayer(FGameplayTag LayerTag) const { return LayerMap.FindRef(LayerTag); }

    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UOverlay* GetRootOverlay() const { return RootOverlay; }

protected:
    virtual void CreateLayerMap();
};
