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
    TSet<TSubclassOf<UUserWidget>> StartupWidgetClasses;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> StartupWidgets;

public:
    UWidgetManagerComponent(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
    void CreateStartupWidgets();
    void RemoveStartupWidgets();
    void ShowStartupWidgets();
    void HideStartupWidgets();
};
