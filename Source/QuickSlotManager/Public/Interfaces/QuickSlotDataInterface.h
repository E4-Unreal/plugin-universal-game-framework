// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotDataInterface.generated.h"

struct FGameplayTag;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UQuickSlotDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class QUICKSLOTMANAGER_API IQuickSlotDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSubclassOf<AActor> GetActorClass() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetSocketTag() const;
};
