// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/TargetWidgetBase.h"
#include "ShopListViewPanelWidget.generated.h"

class UListView;

/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UShopListViewPanelWidget : public UTargetWidgetBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UListView> ShopListView;

protected:
    /* UserWidget */

    virtual void NativeOnInitialized() override;

    /* TargetWidgetBase */

    virtual void BindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent) override;

    /* API */

    virtual void InitializeShopListView();

    UFUNCTION()
    void OnItemDoubleClicked(UObject* Item);
};
