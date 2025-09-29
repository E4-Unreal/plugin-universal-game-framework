// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SlotManagerFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class SLOTMANAGER_API USlotManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* Data */

    UFUNCTION(BlueprintPure, Category = "SlotData")
    static UDataAsset* GetSlotData(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "SlotData")
    static TSoftObjectPtr<UTexture2D> GetThumbnailTexture(UObject* DataObject);
};
