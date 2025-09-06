// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ReplicatedObject.h"
#include "SlotContent.generated.h"

/**
 *
 */
UCLASS()
class SLOTMANAGER_API USlotContent : public UReplicatedObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Replicated)
    TObjectPtr<UDataAsset> Data;

public:
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
