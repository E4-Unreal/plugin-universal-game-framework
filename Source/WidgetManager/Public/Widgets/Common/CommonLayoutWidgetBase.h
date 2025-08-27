// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "CommonLayoutWidgetBase.generated.h"

class UCommonLayerWidgetBase;
class UCommonActivatableWidget;
class UCommonActivatableWidgetStack;

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API UCommonLayoutWidgetBase : public UCommonActivatableWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetStack>> LayerMap;

public:
    UCommonLayoutWidgetBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintPure, meta = (Categories = "Widget.Layer"))
    FORCEINLINE UCommonActivatableWidgetStack* GetLayer(FGameplayTag LayerTag) const { return LayerMap.FindRef(LayerTag); }

    UFUNCTION(BlueprintCallable, meta = (Categories = "Widget.Layer"))
    virtual UCommonActivatableWidget* AddWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable, meta = (Categories = "Widget.Layer"))
    virtual void RemoveWidget(FGameplayTag LayerTag, UCommonActivatableWidget* Widget);

    UFUNCTION(BlueprintCallable)
    virtual UCommonActivatableWidget* AddLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

protected:
    UFUNCTION(BlueprintCallable, meta = (Categories = "Widget.Layer"))
    virtual void SetLayer(FGameplayTag LayerTag, UCommonActivatableWidgetStack* LayerWidget);
};
