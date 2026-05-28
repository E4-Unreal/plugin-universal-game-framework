// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WidgetGameModeBase.generated.h"

class UWidgetManagerComponent;

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API AWidgetGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

protected:
    const static FName WidgetManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetManagerComponent> WidgetManager;

public:
    /* ThisClass */

    AWidgetGameModeBase(const FObjectInitializer& ObjectInitializer);

    /* Getter & Setter */

    UWidgetManagerComponent* GetWidgetManager() const { return WidgetManager; }
};
