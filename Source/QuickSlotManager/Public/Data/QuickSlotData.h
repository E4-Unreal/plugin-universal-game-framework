// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Interfaces/QuickSlotDataInterface.h"
#include "QuickSlotData.generated.h"

/**
 *
 */
UCLASS()
class QUICKSLOTMANAGER_API UQuickSlotData : public UPrimaryDataAsset,
    public IQuickSlotDataInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayTag SocketTag;

public:
    UQuickSlotData(const FObjectInitializer& ObjectInitializer);

    /* QuickSlotDataInterface */

    virtual TSubclassOf<AActor> GetActorClass_Implementation() const override { return ActorClass; }
    virtual FGameplayTag GetSocketTag_Implementation() const override { return SocketTag; }
};
