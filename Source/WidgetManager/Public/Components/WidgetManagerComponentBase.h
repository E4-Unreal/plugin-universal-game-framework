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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;

public:
    UWidgetManagerComponentBase(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual UUserWidget* GetWidgetByClass(TSubclassOf<UUserWidget> WidgetClass) const;

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* GetOrCreateWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);

protected:
    virtual APlayerController* GetOwningPlayerController() const;
    virtual UUserWidget* CreateWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
    virtual bool ShowWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
    virtual bool HideWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
    virtual void ToggleWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
    virtual void DestroyWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);

    virtual void CreateWidgets();
    virtual void DestroyWidgets();

    virtual void CreateStartupWidgets();
    virtual void DestroyStartupWidgets();
    virtual void ShowStartupWidgets();
    virtual void HideStartupWidgets();
    virtual void ToggleStartupWidgets();
};
