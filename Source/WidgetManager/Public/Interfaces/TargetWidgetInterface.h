// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetWidgetInterface.generated.h"

/**
 * 플레이어가 아닌 다른 액터에 대한 정보를 표시하기 위한 위젯 인터페이스
 */
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UTargetWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API ITargetWidgetInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTargetActor(AActor* NewTargetActor);
};
