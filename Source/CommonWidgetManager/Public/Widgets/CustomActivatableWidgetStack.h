// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/TransitionConfig.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CustomActivatableWidgetStack.generated.h"

/**
 * Transition 관련 멤버 변수의 접근 지정자가 protected인 관계로 Setter 메서드가 정의된 커스텀 CommonActivatableWidgetStack 클래스입니다.
 */
UCLASS()
class COMMONWIDGETMANAGER_API UCustomActivatableWidgetStack : public UCommonActivatableWidgetStack
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetTransitionConfig(const FTransitionConfig& TransitionConfig);
};
