// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WidgetStack.generated.h"

class UOverlay;

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UWidgetStack : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UUserWidget> ParentWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UOverlay> Overlay;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> Widgets;

public:
    UWidgetStack(const FObjectInitializer& ObjectInitializer);

    /* ThisClass */

    UFUNCTION(BlueprintCallable)
    UUserWidget* ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    bool HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);
};
