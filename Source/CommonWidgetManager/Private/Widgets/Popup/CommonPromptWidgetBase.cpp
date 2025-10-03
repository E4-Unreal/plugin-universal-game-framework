// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonPromptWidgetBase.h"

#include "CommonButtonBase.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetStringLibrary.h"

UCommonPromptWidgetBase::UCommonPromptWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bShouldNumeric = false;
    MinNum = 0;
    MaxNum = 9999;
}

void UCommonPromptWidgetBase::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    if (GetInputTextBox())
    {
        GetInputTextBox()->SetText(FText::GetEmpty());
    }
}

void UCommonPromptWidgetBase::SetNumeric_Implementation(bool bNewNumeric)
{
    bShouldNumeric = bNewNumeric;

    if (bShouldNumeric && GetInputTextBox())
    {
        GetInputTextBox()->SetText(FText::FromString(FString::FromInt(1)));
    }
}

void UCommonPromptWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetInputTextBox())
    {
        GetInputTextBox()->OnTextChanged.AddDynamic(this, &ThisClass::OnInputTextBoxChanged);
        GetInputTextBox()->OnTextCommitted.AddDynamic(this, &ThisClass::OnInputTextBoxCommitted);
        GetInputTextBox()->SetText(FText::GetEmpty());
        GetInputTextBox()->SetSelectAllTextWhenFocused(true);
    }

    if (GetConfirmButton())
    {
        GetConfirmButton()->OnClicked().AddUObject(this, &ThisClass::OnConfirmButtonClicked);
    }

    if (GetCancelButton())
    {
        GetCancelButton()->OnClicked().AddUObject(this, &ThisClass::OnCancelButtonClicked);
    }
}

void UCommonPromptWidgetBase::OnInputTextBoxChanged_Implementation(const FText& Text)
{
    if (bShouldNumeric)
    {
        FString String = Text.ToString();
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

        if (!String.IsEmpty())
        {
            int64 Value = FMath::Clamp(FCString::Atoi64(*String), MinNum, MaxNum);
            String = FString::FromInt(Value);
        }

        if (GetInputTextBox())
        {
            GetInputTextBox()->SetText(FText::FromString(String));
        }
    }
}

void UCommonPromptWidgetBase::OnInputTextBoxCommitted_Implementation(const FText& Text, ETextCommit::Type CommitMethod)
{
    OnConfirmButtonClicked();
}

void UCommonPromptWidgetBase::OnConfirmButtonClicked_Implementation()
{
    if (OnPromptSubmitted.IsBound())
    {
        OnPromptSubmitted.Execute(GetInputTextBox()->GetText());
        OnPromptSubmitted.Clear();
    }

    DeactivateWidget();
}

void UCommonPromptWidgetBase::OnCancelButtonClicked_Implementation()
{
    DeactivateWidget();
}
