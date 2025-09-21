// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerWidgetManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UPlayerWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "LayoutWidgetInterface"))
    TSubclassOf<UUserWidget> LayoutWidgetClass;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> LayoutWidget;

public:
    UPlayerWidgetManagerComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    UUserWidget* ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    bool HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    void ExecuteBackAction();

protected:
    /* API */

    APlayerController* GetOwningPlayerController() const;
};
