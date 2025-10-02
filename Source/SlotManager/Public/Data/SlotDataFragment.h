// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Flexible/DataFragment.h"
#include "Interfaces/SlotDataInterface.h"
#include "SlotDataFragment.generated.h"

/**
 *
 */
UCLASS()
class SLOTMANAGER_API USlotDataFragment : public UDataFragment, public ISlotDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

public:
    /* SlotDataInterface */

    virtual TSoftObjectPtr<UTexture2D> GetThumbnailTexture_Implementation() const override { return ThumbnailTexture; }
};
