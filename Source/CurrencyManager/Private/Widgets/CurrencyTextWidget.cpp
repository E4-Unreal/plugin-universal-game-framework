// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CurrencyTextWidget.h"

#include "CommonTextBlock.h"
#include "Components/CurrencyManagerComponent.h"
#include "GameplayTags/CurrencyGameplayTags.h"

UCurrencyTextWidget::UCurrencyTextWidget()
{
    TargetCurrencyType = Currency::Default;
    PreviewAmount = 9999;
}

void UCurrencyTextWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    BindEvent();
}

void UCurrencyTextWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (!GetOwningPlayer()) { SetCurrencyText(PreviewAmount); }
    SetCurrencyTextStyle();
}

void UCurrencyTextWidget::SetCurrencyText_Implementation(int64 NewAmount)
{
    if (GetCurrencyTextBlock())
    {
        GetCurrencyTextBlock()->SetText(FText::AsNumber(NewAmount));
    }
}

void UCurrencyTextWidget::SetCurrencyTextStyle()
{
    if (GetCurrencyTextBlock())
    {
        GetCurrencyTextBlock()->SetStyle(TextStyle);
    }
}


void UCurrencyTextWidget::BindEvent_Implementation()
{
    if (APawn* OwningPlayerPawn = GetOwningPlayerPawn())
    {
        if (UCurrencyManagerComponent* CurrencyManager = OwningPlayerPawn->GetComponentByClass<UCurrencyManagerComponent>())
        {
            SetCurrencyText(CurrencyManager->GetCurrencyByType(TargetCurrencyType));
            CurrencyManager->OnUpdate.AddDynamic(this, &ThisClass::OnUpdate);
        }
    }
}

void UCurrencyTextWidget::OnUpdate_Implementation(const FGameplayTag& CurrencyType, int64 Amount)
{
    if (CurrencyType == TargetCurrencyType)
    {
        SetCurrencyText(Amount);
    }
}
