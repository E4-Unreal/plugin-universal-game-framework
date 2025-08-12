// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetManagerComponentBase.h"
#include "WidgetManagerComponent.generated.h"

class UInputAction;

UCLASS(meta = (BlueprintSpawnableComponent))
class WIDGETMANAGER_API UWidgetManagerComponent : public UWidgetManagerComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UInputAction> EscapeAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> EscapeMenuWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UUserWidget>> ToggleableWidgetClassMap;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> EscapeMenuWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<UInputAction>, TObjectPtr<UUserWidget>> ToggleableWidgetMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> ToggleableWidgetStack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<UInputAction>, int32> InputBindingHandleMap;

public:
    UWidgetManagerComponent(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
    UUserWidget* GetWidgetByAction(UInputAction* InputAction) const;
    virtual void ShowWidgetByAction(UInputAction* InputAction);
    virtual void HideWidgetByAction(UInputAction* InputAction);
    virtual void ToggleWidgetByAction(UInputAction* InputAction);
    virtual void HideTopWidget();

    virtual void CreateToggleableWidgets();
    virtual void RemoveToggleableWidgets();
    virtual void SetupInput();
    virtual void BindInput();
    virtual void UnBindInput();

    virtual void CreateEscapeMenuWidget();
    virtual void RemoveEscapeMenuWidget();
    virtual void ShowEscapeMenu();
    virtual void HideEscapeMenu();
};
