// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetManagerComponent.generated.h"

class UInputAction;

UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSet<TSubclassOf<UUserWidget>> StartupWidgetClasses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UUserWidget>> ToggleWidgetClassMap;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> StartupWidgets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<UInputAction>, TObjectPtr<UUserWidget>> ToggleWidgetMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<UInputAction>, int32> InputBindingHandleMap;

public:
    UWidgetManagerComponent(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
    void CreateStartupWidgets();
    void RemoveStartupWidgets();
    void ShowStartupWidgets();
    void HideStartupWidgets();

    void CreateToggleWidgets();
    void RemoveToggleWidgets();
    UUserWidget* GetWidgetByInputAction(UInputAction* InputAction) const;
    void ToggleWidgetByInputAction(UInputAction* InputAction);
    void ShowWidgetByInputAction(UInputAction* InputAction);
    void HideWidgetByInputAction(UInputAction* InputAction);
    void HideToggleWidgets();
    void SetupInput();
    void BindInput();
    void UnBindInput();
};
