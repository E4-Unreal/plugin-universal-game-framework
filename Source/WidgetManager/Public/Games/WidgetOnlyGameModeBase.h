// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WidgetOnlyGameModeBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API AWidgetOnlyGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UUserWidget>> WidgetClasses;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> Widgets;

public:
    virtual void Destroyed() override;

protected:
    AWidgetOnlyGameModeBase(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;

    virtual void CreateWidgets();
    virtual void DestroyWidgets();
    virtual void ShowWidgets();
    virtual void HideWidgets();

    virtual void SetPlayerUIMode();
};
