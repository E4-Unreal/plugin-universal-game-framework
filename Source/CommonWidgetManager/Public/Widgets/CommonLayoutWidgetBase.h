// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
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
class COMMONWIDGETMANAGER_API UCommonLayoutWidgetBase : public UCommonActivatableWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UOverlay> RootOverlay;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FUIInputConfig UIInputConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonLayerWidgetBase> EscapeMenuWidgetClass;

    // TMap<LayerTag, bIsOverlay>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, bool> LayerConfig;

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

    /* API */

    UFUNCTION(BlueprintPure, meta = (Categories = "UI.Layer"))
    FORCEINLINE ULayerStack* GetLayer(FGameplayTag LayerTag) const { return LayerMap.FindRef(LayerTag); }

    UFUNCTION(BlueprintCallable, meta = (Categories = "UI.Layer"))
    virtual UCommonActivatableWidget* ShowWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual UCommonActivatableWidget* ShowLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable, meta = (Categories = "UI.Layer"))
    virtual bool HideWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HideLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable, meta = (Categories = "UI.Layer"))
    virtual void ToggleWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UOverlay* GetRootOverlay() const { return RootOverlay; }

protected:
    virtual void CreateLayerMap();
};
