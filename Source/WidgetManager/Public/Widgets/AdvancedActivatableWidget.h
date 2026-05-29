// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
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
    /* CommonActivatableWidget */

    virtual bool NativeOnHandleBackAction() override;
};
