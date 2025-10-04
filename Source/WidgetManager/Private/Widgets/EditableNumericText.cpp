// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/EditableNumericText.h"

#include "Kismet/KismetStringLibrary.h"

UEditableNumericText::UEditableNumericText()
{
    SetSelectAllTextWhenFocused(true);

    bNumeric = true;
    MinValue = 0;
    MaxValue = INT_MAX;

    OnTextChanged.AddDynamic(this, &ThisClass::NativeOnTextChanged);
}

void UEditableNumericText::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();

    if (bNumeric)
    {
        SetText(FText::FromString(FString::FromInt(MinValue)));
    }
    else
    {
        SetText(FText::GetEmpty());
    }
}

void UEditableNumericText::SelectAllText()
{
    if (MyEditableText.IsValid())
    {
        MyEditableText->SelectAllText();
    }
}

int32 UEditableNumericText::GetValue() const
{
    if (GetText().IsNumeric())
    {
        return FCString::Atoi(*GetText().ToString());
    }

    return MinValue;
}

void UEditableNumericText::SetValue(int32 NewValue)
{
    NewValue = FMath::Clamp(NewValue, MinValue, MaxValue);
    SetText(FText::FromString(FString::FromInt(NewValue)));
}

void UEditableNumericText::NativeOnTextChanged(const FText& NewText)
{
    if (bNumeric)
    {
        FString String = NewText.ToString();
        if (!String.IsNumeric())
        {
            TArray<FString> CharacterArray = UKismetStringLibrary::GetCharacterArrayFromString(String);
            String.Empty();
            for (FString Character : CharacterArray)
            {
                if (Character.IsNumeric())
                {
                    String += Character;
                }
                else
                {
                    break;
                }
            }
        }

        SetValue(FCString::Atoi(*String));
    }
}
