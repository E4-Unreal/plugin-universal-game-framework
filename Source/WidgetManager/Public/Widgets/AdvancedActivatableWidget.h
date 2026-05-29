// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "AdvancedActivatableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBackActionTriggeredEvent);

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UAdvancedActivatableWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FBackActionTriggeredEvent OnBackActionTriggered;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Category = "Config", meta = (Categories = "UI.Layer"))
    FGameplayTag LayerTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Category = "Config")
    FUIInputConfig UIInputConfig;

public:
    UAdvancedActivatableWidget(const FObjectInitializer& ObjectInitializer);

    /* CommonActivatableWidget */

    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

    /* ThisClass */

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

    /* Getter & Setter */

    const FGameplayTag& GetLayerTag() const { return LayerTag; }
    const FUIInputConfig& GetUIInputConfig() const { return UIInputConfig; }

protected:
    /* CommonActivatableWidget */

    virtual bool NativeOnHandleBackAction() override;
};
