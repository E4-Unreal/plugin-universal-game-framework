// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Button.h"
#include "CommonPopupWidgetBase.generated.h"

class UCommonTextBlock;
class UCommonButtonBase;

DECLARE_DYNAMIC_DELEGATE(FButtonClickedDelegate);

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonPopupWidgetBase : public UCommonActivatableWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UCommonTextBlock> TitleTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> MessageTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> ConfirmButton;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UCommonButtonBase> CancelButton;

    UPROPERTY(BlueprintAssignable)
    FOnButtonClickedEvent ConfirmButtonClickedEvent;

    FButtonClickedDelegate ConfirmButtonClickedDelegate;

    UPROPERTY(BlueprintAssignable)
    FOnButtonClickedEvent CancelButtonClickedEvent;

    FButtonClickedDelegate CancelButtonClickedDelegate;

    FSimpleDelegate OnConfirmButtonClickedDelegate;

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTitleText(const FText& TitleText);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMessageText(const FText& MessageText);

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetConfirmButtonClickedDelegate(const FButtonClickedDelegate& NewDelegate) { ConfirmButtonClickedDelegate = NewDelegate; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetCancelButtonClickedDelegate(const FButtonClickedDelegate& NewDelegate) { CancelButtonClickedDelegate = NewDelegate; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetTitleTextBlock() const { return TitleTextBlock; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetMessageTextBlock() const { return MessageTextBlock; }

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
