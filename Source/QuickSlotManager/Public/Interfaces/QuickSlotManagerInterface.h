// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/ScriptDelegateFwd.h"
#include "QuickSlotManagerInterface.generated.h"

class IQuickSlotDataInterface;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuickSlotUpdatedDelegate, int32, SlotIndex);
DECLARE_DYNAMIC_DELEGATE_OneParam(FQuickSlotUpdatedHandler, int32, SlotIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuickSlotIndexChangedDelegate, int32, OldSlotIndex, int32, NewSlotIndex);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FQuickSlotIndexChangedHandler, int32, OldSlotIndex, int32, NewSlotIndex);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UQuickSlotManagerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class QUICKSLOTMANAGER_API IQuickSlotManagerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetSlotNum() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TScriptInterface<IQuickSlotDataInterface> GetSlotData(int32 InSlotIndex) const;

    /* SlotUpdatedDelegate */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindSlotUpdatedHandler(const FQuickSlotUpdatedHandler& Handler);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UnBindSlotUpdatedHandler(const FQuickSlotUpdatedHandler& Handler);

    /* SlotIndexChangedDelegate */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindSlotIndexChangedHandler(const FQuickSlotIndexChangedHandler& Handler);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UnBindSlotIndexChangedHandler(const FQuickSlotIndexChangedHandler& Handler);
};
