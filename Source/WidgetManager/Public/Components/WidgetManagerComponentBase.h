// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetManagerComponentBase.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UWidgetManagerComponentBase : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSet<TSubclassOf<UUserWidget>> StartupWidgetClasses;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> StartupWidgets;

public:
    UWidgetManagerComponentBase(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
    virtual void ShowWidget(UUserWidget* Widget);
    virtual void HideWidget(UUserWidget* Widget);
    virtual void ToggleWidget(UUserWidget* Widget);

    virtual void CreateStartupWidgets();
    virtual void RemoveStartupWidgets();
    virtual void ShowStartupWidgets();
    virtual void HideStartupWidgets();
    virtual void ToggleStartupWidgets();
};
