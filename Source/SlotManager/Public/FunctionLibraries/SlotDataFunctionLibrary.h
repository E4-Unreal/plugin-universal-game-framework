// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SlotDataFunctionLibrary.generated.h"

class UDataDefinitionBase;
/**
 *
 */
UCLASS()
class SLOTMANAGER_API USlotDataFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* Data */

    UFUNCTION(BlueprintPure, Category = "SlotData")
    static bool HasSlotData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "SlotData")
    static TSoftObjectPtr<UTexture2D> GetThumbnailTexture(UDataDefinitionBase* Definition);

protected:
    static UDataAsset* GetSlotData(UDataDefinitionBase* Definition);
};
