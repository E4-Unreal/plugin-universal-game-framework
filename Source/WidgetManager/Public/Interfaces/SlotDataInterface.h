// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlotDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USlotDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API ISlotDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UTexture2D> GetThumbnailTexture() const;
};
