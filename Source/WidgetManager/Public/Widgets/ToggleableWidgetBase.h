// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToggleableWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API UToggleableWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:
    UToggleableWidgetBase(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
