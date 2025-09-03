// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLayerWidgetBase.h"
#include "CommonSystemMenuWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonSystemMenuWidgetBase : public UCommonLayerWidgetBase
{
    GENERATED_BODY()

public:
    UCommonSystemMenuWidgetBase(const FObjectInitializer& ObjectInitializer);
};
