// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PlayerWidgetManagerComponent.h"
#include "CommonPlayerWidgetManagerComponent.generated.h"

/**
 * PlayerController 전용 CommonWidgetManagerComponent
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class COMMONWIDGETMANAGER_API UCommonPlayerWidgetManagerComponent : public UPlayerWidgetManagerComponent
{
    GENERATED_BODY()
};
