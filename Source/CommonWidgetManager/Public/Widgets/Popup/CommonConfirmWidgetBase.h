// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPopupWidgetBase.h"
#include "Components/Button.h"
#include "CommonConfirmWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonConfirmWidgetBase : public UCommonPopupWidgetBase
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
    FButtonClickedDelegate ConfirmButtonClickedDelegate;
    FButtonClickedDelegate CancelButtonClickedDelegate;

public:
    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetConfirmButtonClickedDelegate(const FButtonClickedDelegate& NewDelegate) { ConfirmButtonClickedDelegate = NewDelegate; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetCancelButtonClickedDelegate(const FButtonClickedDelegate& NewDelegate) { CancelButtonClickedDelegate = NewDelegate; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetConfirmButton() const { return ConfirmButton; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetCancelButton() const { return CancelButton; }

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnConfirmButtonClicked();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnCancelButtonClicked();
};
