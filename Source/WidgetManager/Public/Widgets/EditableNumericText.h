// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableText.h"
#include "EditableNumericText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChanged, int32, InValue);

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UEditableNumericText : public UEditableText
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnValueChanged OnValueChanged;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bNumeric;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 MaxValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 MinValue;

public:
    UEditableNumericText();

    /* UWidget */

    virtual void OnWidgetRebuilt() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    void SelectAllText();

    UFUNCTION(BlueprintPure)
    virtual int32 GetValue() const;

    UFUNCTION(BlueprintCallable)
    virtual void SetValue(int32 NewValue);

protected:
    /* EditableText */

    UFUNCTION()
    virtual void NativeOnTextChanged(const FText& NewText);
};
