// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SlotManagerInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSlotUpdatedDelegate, int32, SlotIndex);

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USlotManagerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SLOTMANAGER_API ISlotManagerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetMaxSlotNum() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetData(int32 SlotIndex) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* GetDataInstance(int32 SlotIndex) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool IsSlotEmpty(int32 SlotIndex) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SwapSlots(UActorComponent* Source, int32 SourceIndex, UActorComponent* Destination, int32 DestinationIndex);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindOnSlotUpdated(const FSlotUpdatedDelegate& SlotUpdatedDelegate);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UnbindOnSlotUpdated(const FSlotUpdatedDelegate& SlotUpdatedDelegate);
};
