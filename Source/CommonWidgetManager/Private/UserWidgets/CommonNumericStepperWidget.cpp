// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/CommonNumericStepperWidget.h"
#include "CommonButtonBase.h"

#include "Widgets/EditableNumericText.h"

void UCommonNumericStepperWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetIncreaseButton())
    {
        GetIncreaseButton()->OnClicked().AddUObject(this, &ThisClass::OnIncreaseButtonClicked);
    }

    if (GetDecreaseButton())
    {
        GetDecreaseButton()->OnClicked().AddUObject(this, &ThisClass::OnDecreaseButtonClicked);
    }
}

void UCommonNumericStepperWidget::OnIncreaseButtonClicked()
{
    if (GetEditableNumericText())
    {
        GetEditableNumericText()->SetValue(GetEditableNumericText()->GetValue() + 1);
    }
}

void UCommonNumericStepperWidget::OnDecreaseButtonClicked()
{
    if (GetEditableNumericText())
    {
        GetEditableNumericText()->SetValue(GetEditableNumericText()->GetValue() - 1);
    }
}
