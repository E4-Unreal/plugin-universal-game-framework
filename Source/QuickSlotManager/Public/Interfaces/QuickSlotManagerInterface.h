// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/SlotManagerInterface.h"
#include "QuickSlotManagerInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UQuickSlotManagerInterface : public USlotManagerInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class QUICKSLOTMANAGER_API IQuickSlotManagerInterface : public ISlotManagerInterface
{
    GENERATED_BODY()
};
