// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WidgetOnlyGameModeBase.generated.h"

class UWidgetManagerComponentBase;

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API AWidgetOnlyGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

protected:
    const static FName WidgetManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetManagerComponentBase> WidgetManager;

public:
    AWidgetOnlyGameModeBase(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

public:
    FORCEINLINE UWidgetManagerComponentBase* GetWidgetManager() const { return WidgetManager; }
};
