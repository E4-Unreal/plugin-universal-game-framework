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
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UUserWidget>> PanelWidgetClassMap;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> EscapeMenuWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> PanelWidgets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<UInputAction>, int32> InputBindingHandleMap;

public:
    UWidgetManagerComponent(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual bool ShowPanelWidget(TSubclassOf<UUserWidget> PanelWidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HidePanelWidget(TSubclassOf<UUserWidget> PanelWidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void TogglePanelWidget(TSubclassOf<UUserWidget> PanelWidgetClass);

protected:
    /* WidgetManagerComponentBase */

    virtual void CreateWidgets() override;
    virtual void DestroyWidgets() override;

    /* API */

    virtual void BindInput();
    virtual void UnBindInput();
    virtual void OnEscapeActionTriggered();

    virtual void CreatePanelWidgets();
    virtual void DestroyPanelWidgets();
    TSubclassOf<UUserWidget> GetWidgetClassByAction(UInputAction* InputAction) const;
    virtual bool ShowWidgetByAction(UInputAction* InputAction);
    virtual bool HideWidgetByAction(UInputAction* InputAction);
    virtual void ToggleWidgetByAction(UInputAction* InputAction);
    virtual void HideTopWidget();

    virtual void CreateEscapeMenuWidget();
    virtual void DestroyEscapeMenuWidget();
    virtual bool ShowEscapeMenu();
    virtual bool HideEscapeMenu();
    virtual void ToggleEscapeMenu();
};
