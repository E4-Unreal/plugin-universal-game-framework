// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLayerWidgetBase.h"
#include "CommonGameOverlayWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonGameOverlayWidgetBase : public UCommonLayerWidgetBase
{
    GENERATED_BODY()

public:
    UCommonGameOverlayWidgetBase(const FObjectInitializer& ObjectInitializer);
};
