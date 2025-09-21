// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPopupWidgetBase.h"
#include "Components/Button.h"
#include "Interfaces/ConfirmWidgetInterface.h"
#include "CommonConfirmWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonConfirmWidgetBase : public UCommonPopupWidgetBase, public IConfirmWidgetInterface
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> ConfirmButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> CancelButton;

public:
    UPROPERTY(BlueprintAssignable)
    FOnButtonClickedEvent ConfirmButtonClickedEvent;

    UPROPERTY(BlueprintAssignable)
    FOnButtonClickedEvent CancelButtonClickedEvent;

protected:
    FOnButtonClicked OnConfirmButtonClicked;

public:
    /* ConfirmWidgetInterface */

    virtual void BindOnConfirmButtonClicked_Implementation(const FOnButtonClicked& NewDelegate) override { OnConfirmButtonClicked = NewDelegate; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetConfirmButton() const { return ConfirmButton; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetCancelButton() const { return CancelButton; }

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void HandleOnConfirmButtonClicked();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void HandleOnCancelButtonClicked();
};
