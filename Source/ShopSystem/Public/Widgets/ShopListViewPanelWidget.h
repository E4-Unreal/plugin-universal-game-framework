// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/PopupWidgetInterface.h"
#include "Interfaces/PromptWidgetInterface.h"
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

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText BuyPromptTitleText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText BuyPromptMessageText;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UListView> ShopListView;

    FOnWidgetHidden WidgetHiddenDelegate;
    FOnPromptSubmitted PromptSubmittedDelegate;

protected:
    UShopListViewPanelWidget(const FObjectInitializer& ObjectInitializer);

    /* UserWidget */

    virtual void NativeOnInitialized() override;

    /* TargetWidgetBase */

    virtual void BindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent) override;
    virtual void UnbindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent) override;

    /* API */

    virtual void InitializeShopListView();

    UFUNCTION()
    virtual void OnItemDoubleClicked(UObject* Item);

    UFUNCTION()
    virtual void OnSlotUpdated(int32 Index);

    UFUNCTION()
    virtual void OnWidgetHidden();

    UFUNCTION()
    virtual void OnPromptSubmitted(const FText& SubmittedText);
};
