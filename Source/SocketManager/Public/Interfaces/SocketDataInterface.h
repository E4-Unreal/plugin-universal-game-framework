// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "SocketDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USocketDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SOCKETMANAGER_API ISocketDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetSocketType() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FName GetSocketName() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UStaticMesh> GetStaticMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftClassPtr<AActor> GetActorClass() const;
};
