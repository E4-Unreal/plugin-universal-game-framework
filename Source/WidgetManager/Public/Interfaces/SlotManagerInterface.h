// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlotManagerInterface.generated.h"

class ISlotDataInterface;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSlotUpdatedDelegate, int32, SlotIndex);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSlotUpdatedHandler, int32, SlotIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlotIndexChangedDelegate, int32, OldSlotIndex, int32, NewSlotIndex);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSlotIndexChangedHandler, int32, OldSlotIndex, int32, NewSlotIndex);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USlotManagerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API ISlotManagerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetSlotNum() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TScriptInterface<ISlotDataInterface> GetSlotData(int32 InSlotIndex) const;

    /* SlotUpdatedDelegate */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindSlotUpdatedHandler(const FSlotUpdatedHandler& Handler);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UnBindSlotUpdatedHandler(const FSlotUpdatedHandler& Handler);

    /* SlotIndexChangedDelegate */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindSlotIndexChangedHandler(const FSlotIndexChangedHandler& Handler);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UnBindSlotIndexChangedHandler(const FSlotIndexChangedHandler& Handler);
};
