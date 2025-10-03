// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPopupWidgetBase.h"
#include "Components/Button.h"
#include "Interfaces/PromptWidgetInterface.h"
#include "CommonPromptWidgetBase.generated.h"

class UEditableTextBox;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonPromptWidgetBase : public UCommonPopupWidgetBase, public IPromptWidgetInterface
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bShouldNumeric;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int64 MaxNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int64 MinNum;

protected:
    FOnPromptSubmitted OnPromptSubmitted;

public:
    UCommonPromptWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* CommonActivatableWidget */

    virtual void NativeOnDeactivated() override;

    /* PromptWidgetInterface */

    virtual void BindOnPromptSubmitted_Implementation(const FOnPromptSubmitted& NewDelegate) override { OnPromptSubmitted = NewDelegate; }
    virtual void SetNumeric_Implementation(bool bNewNumeric) override;
    virtual void SetMaxValue_Implementation(float NewMaxValue) override { MaxNum = NewMaxValue; }
    virtual void SetMinValue_Implementation(float NewMinValue) override { MinNum = NewMinValue; }

    /* Components */

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
