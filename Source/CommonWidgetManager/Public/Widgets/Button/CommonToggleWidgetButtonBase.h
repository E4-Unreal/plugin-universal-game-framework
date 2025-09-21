// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonToggleWidgetButtonBase.generated.h"

class UCommonLayerWidgetBase;

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGER_API UCommonToggleWidgetButtonBase : public UCommonButtonBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "LayerWidgetInterface"))
    TSubclassOf<UUserWidget> WidgetClass;

protected:
    virtual void NativeOnClicked() override;
};
