// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SocketSlot.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FSocketSlot
{
    GENERATED_BODY()

    static const FSocketSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SocketTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Actor;

    bool operator==(const FSocketSlot& Other) const { return SocketTag == Other.SocketTag && Actor == Other.Actor; }
    bool operator!=(const FSocketSlot& Other) const { return !(*this == Other); }

    bool IsValid() const { return SocketTag.IsValid() && Actor; }
};
