// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/NumericStepperWidget.h"

#include "Components/Button.h"
#include "Widgets/EditableNumericText.h"

void UNumericStepperWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetIncreaseButton())
    {
        GetIncreaseButton()->OnClicked.AddDynamic(this, &ThisClass::OnIncreaseButtonClicked);
    }

    if (GetDecreaseButton())
    {
        GetDecreaseButton()->OnClicked.AddDynamic(this, &ThisClass::OnDecreaseButtonClicked);
    }
}

void UNumericStepperWidget::OnIncreaseButtonClicked()
{
    if (GetEditableNumericText())
    {
        GetEditableNumericText()->SetValue(GetEditableNumericText()->GetValue() + 1);
    }
}

void UNumericStepperWidget::OnDecreaseButtonClicked()
{
    if (GetEditableNumericText())
    {
        GetEditableNumericText()->SetValue(GetEditableNumericText()->GetValue() - 1);
    }
}
