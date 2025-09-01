// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPopupWidgetBase.h"
#include "CommonPromptWidgetBase.generated.h"

class UEditableTextBox;
DECLARE_DYNAMIC_DELEGATE_OneParam(FPromptSubmittedDelegate, const FText&, InputText);

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonPromptWidgetBase : public UCommonPopupWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UEditableTextBox> InputTextBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> ConfirmButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> CancelButton;

public:
    UPROPERTY(BlueprintAssignable)
    FOnButtonClickedEvent ConfirmButtonClickedEvent;

    UPROPERTY(BlueprintAssignable)
    FOnButtonClickedEvent CancelButtonClickedEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bShouldNumeric;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int64 MaxNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int64 MinNum;

protected:
    FPromptSubmittedDelegate ConfirmButtonClickedDelegate;
    FButtonClickedDelegate CancelButtonClickedDelegate;

public:
    UCommonPromptWidgetBase();

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetConfirmButtonClickedDelegate(const FPromptSubmittedDelegate& NewDelegate) { ConfirmButtonClickedDelegate = NewDelegate; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetCancelButtonClickedDelegate(const FButtonClickedDelegate& NewDelegate) { CancelButtonClickedDelegate = NewDelegate; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UEditableTextBox* GetInputTextBox() const { return InputTextBox; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetConfirmButton() const { return ConfirmButton; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetCancelButton() const { return CancelButton; }

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnInputTextBoxChanged(const FText& Text);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnInputTextBoxCommitted(const FText& Text, ETextCommit::Type CommitMethod);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnConfirmButtonClicked();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnCancelButtonClicked();
};
