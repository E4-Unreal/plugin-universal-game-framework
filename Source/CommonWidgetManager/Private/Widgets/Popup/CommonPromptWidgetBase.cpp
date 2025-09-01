// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Popup/CommonPromptWidgetBase.h"

#include "CommonButtonBase.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetStringLibrary.h"

UCommonPromptWidgetBase::UCommonPromptWidgetBase()
{
    bShouldNumeric = false;
    MinNum = 0;
    MaxNum = 9999;
}

void UCommonPromptWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetInputTextBox())
    {
        GetInputTextBox()->OnTextChanged.AddDynamic(this, &ThisClass::OnInputTextBoxChanged);
        GetInputTextBox()->OnTextCommitted.AddDynamic(this, &ThisClass::OnInputTextBoxCommitted);
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
            FString NewString;
            TArray<FString> CharacterArray = UKismetStringLibrary::GetCharacterArrayFromString(String);
            for (FString Character : CharacterArray)
            {
                if (Character.IsNumeric())
                {
                    NewString += Character;
                }
                else
                {
                    break;
                }
            }

            if (GetInputTextBox())
            {
                GetInputTextBox()->SetText(FText::FromString(NewString));
            }
        }
    }
}

void UCommonPromptWidgetBase::OnInputTextBoxCommitted_Implementation(const FText& Text, ETextCommit::Type CommitMethod)
{
    OnConfirmButtonClicked();
}

void UCommonPromptWidgetBase::OnConfirmButtonClicked_Implementation()
{
    DeactivateWidget();

    if (ConfirmButtonClickedDelegate.IsBound())
    {
        ConfirmButtonClickedDelegate.Execute(GetInputTextBox()->GetText());
        ConfirmButtonClickedDelegate.Clear();
    }

    ConfirmButtonClickedEvent.Broadcast();
}

void UCommonPromptWidgetBase::OnCancelButtonClicked_Implementation()
{
    DeactivateWidget();

    if (CancelButtonClickedDelegate.IsBound())
    {
        CancelButtonClickedDelegate.Execute();
        CancelButtonClickedDelegate.Clear();
    }

    CancelButtonClickedEvent.Broadcast();
}
