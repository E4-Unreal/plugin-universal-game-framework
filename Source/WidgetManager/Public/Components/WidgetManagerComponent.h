// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSet<TSubclassOf<UUserWidget>> DefaultWidgetClasses;

public:
    UWidgetManagerComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* ThisClass */

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);
};
