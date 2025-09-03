// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommonPawnWidgetManagerComponent.generated.h"

class UCommonLayerWidgetBase;
class UInputAction;

/**
 * Pawn 전용 CommonWidgetManagerComponent
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class COMMONWIDGETMANAGER_API UCommonPawnWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UCommonLayerWidgetBase>> ToggleableLayerWidgetMap;

public:
    /* ActorComponent */

    virtual void BeginPlay() override;

protected:
    FORCEINLINE APawn* GetOwningPawn() const { return CastChecked<APawn>(GetOwner()); }
    virtual void BindActions();
    virtual void ToggleLayerWidget(TSubclassOf<UCommonLayerWidgetBase> LayerWidgetClass);
};
