// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SocketActorSlot.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FSocketActorSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SocketTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Actor;

    bool operator==(const FSocketActorSlot &Other) const { return SocketTag == Other.SocketTag && Actor == Other.Actor; }
    bool operator!=(const FSocketActorSlot &Other) const { return !(*this == Other); }
};
