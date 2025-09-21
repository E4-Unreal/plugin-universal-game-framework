// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopupWidgetInterface.h"
#include "AlertWidgetInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UAlertWidgetInterface : public UPopupWidgetInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IAlertWidgetInterface : public IPopupWidgetInterface
{
    GENERATED_BODY()

public:
};
