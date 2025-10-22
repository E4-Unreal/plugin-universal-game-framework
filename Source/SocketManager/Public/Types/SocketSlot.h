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
    FGameplayTag SocketType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer SocketTypesToHide;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer HiddenBySocketTypes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Actor;

    bool operator==(const FSocketSlot& Other) const { return SocketType == Other.SocketType && Actor == Other.Actor; }
    bool operator!=(const FSocketSlot& Other) const { return !(*this == Other); }

    bool IsValid() const { return SocketType.IsValid() && Actor; }
};
