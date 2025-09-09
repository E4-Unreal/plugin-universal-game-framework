// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemActorInterface.generated.h"

class UDataInstanceBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class UItemActorInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * ItemActor 설정 전용 인터페이스
 */
class INVENTORYSYSTEM_API IItemActorInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetItemInstances(const TArray<UDataInstanceBase*>& NewItemsInstances);
};
