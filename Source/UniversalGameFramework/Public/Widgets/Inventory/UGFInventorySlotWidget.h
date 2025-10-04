// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/PopupWidgetInterface.h"
#include "Interfaces/PromptWidgetInterface.h"
#include "Widgets/InventorySlotWidget.h"
#include "UGFInventorySlotWidget.generated.h"

class UShopComponent;

/**
 *
 */
UCLASS(Abstract)
class UNIVERSALGAMEFRAMEWORK_API UUGFInventorySlotWidget : public UInventorySlotWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText SellPromptTitleText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText SellPromptMessageText;

protected:
    FOnWidgetHidden WidgetHiddenDelegate;
    FOnPromptSubmitted PromptSubmittedDelegate;

public:
    UUGFInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

protected:
    /* UserWidget */

    virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    /* API */

    virtual UShopComponent* GetShopComponent() const;
    virtual bool IsPlayerInventory() const;
    virtual bool IsTrading() const;
    virtual void ShowSellPromptPopup() const;

    UFUNCTION()
    virtual void OnWidgetHidden();

    UFUNCTION()
    virtual void OnPromptSubmitted(const FText& SubmittedText);
};
