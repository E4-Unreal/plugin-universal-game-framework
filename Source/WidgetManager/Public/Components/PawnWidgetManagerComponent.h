// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputManager/Public/Components/PawnInputManagerComponentBase.h"
#include "PawnWidgetManagerComponent.generated.h"

class UInputAction;

UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UPawnWidgetManagerComponent : public UPawnInputManagerComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UUserWidget>> ToggleableWidgetMap;

public:
    UPawnWidgetManagerComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* PawnInputManagerComponentBase */

    virtual TArray<FInputActionConfigData> GetInputActionConfigs() override;
    virtual void OnInputActionTriggered_Implementation(const FInputActionInstance& InputActionInstance) override;

protected:
    /* API */

    virtual UUserWidget* ShowHUDWidget(AActor* PlayerActor);
    virtual bool HideHUDWidget(AActor* PlayerActor);
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

    virtual void BindControllerChangedEvent();
    virtual void UnBindControllerChangedEvent();

    UFUNCTION()
    virtual void OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);
};
