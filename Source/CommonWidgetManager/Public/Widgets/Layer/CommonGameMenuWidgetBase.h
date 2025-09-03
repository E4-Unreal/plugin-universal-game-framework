// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLayerWidgetBase.h"
#include "CommonGameMenuWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonGameMenuWidgetBase : public UCommonLayerWidgetBase
{
    GENERATED_BODY()

public:
    UCommonGameMenuWidgetBase(const FObjectInitializer& ObjectInitializer);
};
