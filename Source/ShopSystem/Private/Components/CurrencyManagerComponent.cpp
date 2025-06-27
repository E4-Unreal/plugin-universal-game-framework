// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CurrencyManagerComponent.h"

#include "ShopGameplayTags.h"


UCurrencyManagerComponent::UCurrencyManagerComponent()
{
    bWantsInitializeComponent = true;

    DefaultCurrencies.Emplace(Currency::Default, 0);
}

void UCurrencyManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    for (const auto& [CurrencyType, Amount] : DefaultCurrencies)
    {
        CurrencyMap.Emplace(CurrencyType, Amount);
    }
}

int32 UCurrencyManagerComponent::GetCurrency(const FGameplayTag& CurrencyType) const
{
    const int32* CurrencyPtr = CurrencyMap.Find(CurrencyType);
    return CurrencyPtr ? *CurrencyPtr : 0;
}

bool UCurrencyManagerComponent::AddCurrency(const FGameplayTag& CurrencyType, int32 Amount)
{
    if (bool bCanAdd = Amount > 0 && CurrencyMap.Contains(CurrencyType); !bCanAdd) return false;

    CurrencyMap.Emplace(CurrencyType, GetCurrency(CurrencyType) + Amount);

    return true;
}

bool UCurrencyManagerComponent::RemoveCurrency(const FGameplayTag& CurrencyType, int32 Amount)
{
    if (bool bCanRemove = Amount > 0 && GetCurrency(CurrencyType) > Amount; !bCanRemove) return false;

    CurrencyMap.Emplace(CurrencyType, GetCurrency(CurrencyType) - Amount);

    return true;
}
