// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlotDataInterface.generated.h"

class USlotContent;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USlotDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SLOTMANAGER_API ISlotDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UTexture2D> GetThumbnailTexture() const;
};
