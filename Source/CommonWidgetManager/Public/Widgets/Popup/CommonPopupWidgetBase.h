// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/PopupWidgetInterface.h"
#include "Widgets/Layer/CommonLayerWidgetBase.h"
#include "CommonPopupWidgetBase.generated.h"

class UCommonTextBlock;
class UCommonButtonBase;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonPopupWidgetBase : public UCommonLayerWidgetBase, public IPopupWidgetInterface
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UCommonTextBlock> TitleTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> MessageTextBlock;

protected:
    FOnWidgetHidden OnWidgetHidden;

public:
    UCommonPopupWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* CommonActivatableWidget */

    virtual void NativeOnDeactivated() override;

    /* PopupWidgetInterface */

    virtual void SetTitleText_Implementation(const FText& NewTitleText) override;
    virtual void SetMessageText_Implementation(const FText& NewMessageText) override;
    virtual void BindOnWidgetHidden_Implementation(const FOnWidgetHidden& NewDelegate) override { OnWidgetHidden = NewDelegate; }

    /* Components */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetTitleTextBlock() const { return TitleTextBlock; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetMessageTextBlock() const { return MessageTextBlock; }
};
