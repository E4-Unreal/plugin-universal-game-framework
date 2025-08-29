// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "CommonLayerWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonLayerWidgetBase : public UCommonActivatableWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "UI.Layer"))
    FGameplayTag LayerTag;

public:
    UCommonLayerWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* API */

    UFUNCTION(BlueprintPure)
    FGameplayTag GetLayerTag() const { return LayerTag; }
};
