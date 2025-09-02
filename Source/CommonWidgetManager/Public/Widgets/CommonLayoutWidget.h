// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLayoutWidgetBase.h"
#include "CommonLayoutWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonLayoutWidget : public UCommonLayoutWidgetBase
{
    GENERATED_BODY()

public:
    UCommonLayoutWidget(const FObjectInitializer& ObjectInitializer);
};
