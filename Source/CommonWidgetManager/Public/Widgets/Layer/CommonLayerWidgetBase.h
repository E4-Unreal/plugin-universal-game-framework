// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "Interfaces/LayerWidgetInterface.h"
#include "CommonLayerWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonLayerWidgetBase : public UCommonActivatableWidget, public ILayerWidgetInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FUIInputConfig UIInputConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "UI.Layer"))
    FGameplayTag LayerTag;

public:
    UCommonLayerWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* CommonActivatableWidget */

    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

    /* LayerWidgetInterface */

    virtual FGameplayTag GetLayerTag_Implementation() const override { return LayerTag; }
};
