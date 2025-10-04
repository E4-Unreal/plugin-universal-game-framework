// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommonNumericStepperWidget.generated.h"

class UEditableNumericText;
class UCommonButtonBase;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonNumericStepperWidget : public UUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UEditableNumericText> EditableNumericText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UCommonButtonBase> IncreaseButton;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UCommonButtonBase> DecreaseButton;

public:
    /* UserWidget */

    virtual void NativeOnInitialized() override;

    /* Components */

    FORCEINLINE UEditableNumericText* GetEditableNumericText() const { return EditableNumericText; }
    FORCEINLINE UCommonButtonBase* GetIncreaseButton() const { return IncreaseButton; }
    FORCEINLINE UCommonButtonBase* GetDecreaseButton() const { return DecreaseButton; }

protected:
    UFUNCTION()
    virtual void OnIncreaseButtonClicked();

    UFUNCTION()
    virtual void OnDecreaseButtonClicked();
};
