// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotWidgetInterface.generated.h"

class IQuickSlotManagerInterface;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UQuickSlotWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class QUICKSLOTMANAGER_API IQuickSlotWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetQuickSlotManager(const TScriptInterface<IQuickSlotManagerInterface>& QuickSlotManager);
};
