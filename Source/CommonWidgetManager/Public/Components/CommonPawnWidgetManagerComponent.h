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
    TSubclassOf<UUserWidget> HUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UUserWidget>> ToggleableWidgetMap;

public:
    /* ActorComponent */

    virtual void BeginPlay() override;

protected:
    virtual void BindEvents();
    virtual void ToggleWidget(TSubclassOf<UUserWidget> LayerWidgetClass);
    virtual void ShowHUDWidget(AActor* PlayerActor);
    virtual void HideHUDWidget(AActor* PlayerActor);

    UFUNCTION()
    virtual void OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);
};
