// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnWidgetManagerComponent.h"
#include "CommonPawnWidgetManagerComponent.generated.h"

/**
 * Pawn 전용 CommonWidgetManagerComponent
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class COMMONWIDGETMANAGER_API UCommonPawnWidgetManagerComponent : public UPawnWidgetManagerComponent
{
    GENERATED_BODY()
};
