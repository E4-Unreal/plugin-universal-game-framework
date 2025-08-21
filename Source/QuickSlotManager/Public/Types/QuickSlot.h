// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "QuickSlot.generated.h"

USTRUCT(BlueprintType)
struct QUICKSLOTMANAGER_API FQuickSlot
{
    GENERATED_BODY()

    static const FQuickSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SocketTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Actor;

    FORCEINLINE bool operator==(const FQuickSlot& Other) const { return SocketTag == Other.SocketTag && Actor == Other.Actor; }
    FORCEINLINE bool operator!=(const FQuickSlot& Other) const { return !(*this == Other); }

    bool IsValid() const { return SocketTag.IsValid() && Actor; }
};
