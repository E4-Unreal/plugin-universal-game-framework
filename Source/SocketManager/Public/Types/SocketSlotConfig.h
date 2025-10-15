// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SocketSlotConfig.generated.h"

USTRUCT(BlueprintType)
struct SOCKETMANAGER_API FSocketSlotConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SocketTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UStaticMesh> DefaultStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USkeletalMesh> DefaultSkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> DefaultActorClass;

    bool IsValid() const { return SocketTag.IsValid(); }
};
