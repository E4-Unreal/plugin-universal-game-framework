// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotActorInterface.generated.h"

class IQuickSlotDataInterface;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UQuickSlotActorInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class QUICKSLOTMANAGER_API IQuickSlotActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetQuickSlotData();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetQuickSlotData(const TScriptInterface<IQuickSlotDataInterface>& NewData);
};
