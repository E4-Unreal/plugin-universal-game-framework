// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/UGFItem.h"
#include "UObject/Interface.h"
#include "UGFItemActorInterface.generated.h"

UINTERFACE()
class UGFITEMSYSTEM_API UUGFItemActorInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class UGFITEMSYSTEM_API IUGFItemActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetItem(const FUGFItem& InItem);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetItems(const TArray<FUGFItem>& InItems);
};
