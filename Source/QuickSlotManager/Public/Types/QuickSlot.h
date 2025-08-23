// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interfaces/QuickSlotDataInterface.h"
#include "QuickSlot.generated.h"


USTRUCT(BlueprintType)
struct QUICKSLOTMANAGER_API FQuickSlot
{
    GENERATED_BODY()

    static const FQuickSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IQuickSlotDataInterface> Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Actor;

    TSubclassOf<AActor> GetActorClass() const { return Data.GetObject() ? IQuickSlotDataInterface::Execute_GetActorClass(Data.GetObject()) : nullptr; }
    FGameplayTag GetSocketTag() const { return Data.GetObject() ? IQuickSlotDataInterface::Execute_GetSocketTag(Data.GetObject()) : FGameplayTag::EmptyTag; }

    FORCEINLINE bool operator==(const FQuickSlot& Other) const { return Data == Other.Data && Actor == Other.Actor; }
    FORCEINLINE bool operator!=(const FQuickSlot& Other) const { return !(*this == Other); }

    bool IsEmpty() const { return !Data; }
};
