// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NumericStepperWidget.generated.h"

class UEditableNumericText;
class UButton;

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API UNumericStepperWidget : public UUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UEditableNumericText> EditableNumericText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UButton> IncreaseButton;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UButton> DecreaseButton;

public:
    /* UserWidget */

    virtual void NativeOnInitialized() override;

    /* Components */

    FORCEINLINE UEditableNumericText* GetEditableNumericText() const { return EditableNumericText; }
    FORCEINLINE UButton* GetIncreaseButton() const { return IncreaseButton; }
    FORCEINLINE UButton* GetDecreaseButton() const { return DecreaseButton; }

protected:
    UFUNCTION()
    virtual void OnIncreaseButtonClicked();

    UFUNCTION()
    virtual void OnDecreaseButtonClicked();
};
