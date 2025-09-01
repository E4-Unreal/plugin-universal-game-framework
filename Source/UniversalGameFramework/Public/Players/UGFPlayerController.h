// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UGFPlayerController.generated.h"

class UCommonWidgetManagerComponent;

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    const static FName WidgetManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCommonWidgetManagerComponent> WidgetManager;

public:
    AUGFPlayerController(const FObjectInitializer& ObjectInitializer);

    FORCEINLINE UCommonWidgetManagerComponent* GetWidgetManager() const { return WidgetManager; }
};
