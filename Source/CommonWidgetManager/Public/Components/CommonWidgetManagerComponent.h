// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommonWidgetManagerComponent.generated.h"


class UCommonLayoutWidgetBase;
class UCommonActivatableWidget;

/**
 * PlayerController 전용 액터 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class COMMONWIDGETMANAGER_API UCommonWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonLayoutWidgetBase> LayoutWidgetClass;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UCommonLayoutWidgetBase> LayoutWidget;

public:
    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    UFUNCTION(BlueprintPure)
    virtual APlayerController* GetOwningPlayerController() const;

    UFUNCTION(BlueprintPure)
    UCommonLayoutWidgetBase* GetLayoutWidget() const { return LayoutWidget; }
};
