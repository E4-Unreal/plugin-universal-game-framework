// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UGFPlayerController.generated.h"

class UPlayerWidgetManagerComponent;

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    const static FName PlayerWidgetManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UPlayerWidgetManagerComponent> PlayerWidgetManager;

public:
    AUGFPlayerController(const FObjectInitializer& ObjectInitializer);

    FORCEINLINE UPlayerWidgetManagerComponent* GetPlayerWidgetManager() const { return PlayerWidgetManager; }
};
