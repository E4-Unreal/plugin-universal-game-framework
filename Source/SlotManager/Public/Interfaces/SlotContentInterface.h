// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlotContentInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USlotContentInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SLOTMANAGER_API ISlotContentInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* GetInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const;
};
