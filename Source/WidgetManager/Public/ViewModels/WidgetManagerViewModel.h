// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "WidgetManagerViewModel.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UWidgetManagerViewModel : public UMVVMViewModelBase
{
    GENERATED_BODY()

public:
    /* ThisClass */

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);
};
