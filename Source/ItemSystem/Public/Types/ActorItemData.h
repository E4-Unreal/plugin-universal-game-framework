// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "ActorItemData.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FActorItemData : public FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    static const FActorItemData EmptyData;

    FORCEINLINE bool operator ==(const FActorItemData& Other) const
    {
        return StaticMesh == Other.StaticMesh;
    }

    FORCEINLINE bool operator !=(const FActorItemData& Other) const
    {
        return !(*this == Other);
    }
};
