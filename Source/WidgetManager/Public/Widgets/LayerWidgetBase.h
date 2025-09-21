// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/LayerWidgetInterface.h"
#include "LayerWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API ULayerWidgetBase : public UUserWidget, public ILayerWidgetInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "UI.Layer"))
    FGameplayTag LayerTag;

public:
    ULayerWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* LayerWidgetInterface */

    virtual FGameplayTag GetLayerTag_Implementation() const override { return LayerTag; }
};
