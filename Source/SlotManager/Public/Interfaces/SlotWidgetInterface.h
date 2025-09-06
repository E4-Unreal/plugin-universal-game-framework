// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlotWidgetInterface.generated.h"

class ISlotDataInterface;
class ISlotManagerInterface;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USlotWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SLOTMANAGER_API ISlotWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TScriptInterface<ISlotManagerInterface> GetSlotManager() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSlotManager(const TScriptInterface<ISlotManagerInterface>& NewSlotManager);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetSlotIndex() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSlotIndex(int32 NewSlotIndex);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Refresh();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Clear();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void ApplyData(const TScriptInterface<ISlotDataInterface>& NewData);
};
