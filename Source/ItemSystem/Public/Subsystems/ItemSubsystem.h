// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemSubsystem.generated.h"

class UItemDefinition;

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UItemSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    UItemDefinition* GetItemDefinitionByID(int32 ID);
};
