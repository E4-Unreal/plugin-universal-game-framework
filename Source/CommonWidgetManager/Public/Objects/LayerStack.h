// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LayerStack.generated.h"

class UCommonActivatableWidgetStack;
class UOverlay;
class UCommonActivatableWidget;
struct FGameplayTag;

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGER_API ULayerStack : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UUserWidget> ParentWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UCommonActivatableWidgetStack> Stack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UOverlay> Overlay;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UCommonActivatableWidgetStack>> OverlayStack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TSubclassOf<UCommonActivatableWidget>, TObjectPtr<UCommonActivatableWidget>> ActivatedWidgetMap;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsOverlay() const { return Stack == nullptr; }

    UFUNCTION(BlueprintCallable)
    virtual void InitializeAsStack(UUserWidget* NewParentWidget, UCommonActivatableWidgetStack* NewStack);

    UFUNCTION(BlueprintCallable)
    virtual void InitializeAsOverlayStack(UUserWidget* NewParentWidget, UOverlay* NewOverlay);

    UFUNCTION(BlueprintCallable)
    virtual UCommonActivatableWidget* ShowWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HideWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass);

protected:
    virtual UCommonActivatableWidget* AddWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass);
    virtual UCommonActivatableWidget* AddWidgetToOverlayStack(TSubclassOf<UCommonActivatableWidget> WidgetClass);
    virtual void SortOverlayStack();
    virtual UCommonActivatableWidgetStack* AddStackInstance();
};
