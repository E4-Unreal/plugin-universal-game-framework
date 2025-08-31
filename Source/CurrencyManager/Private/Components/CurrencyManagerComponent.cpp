// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CurrencyManagerComponent.h"

#include "GameplayTags/CurrencyGameplayTags.h"


UCurrencyManagerComponent::UCurrencyManagerComponent()
{
    bWantsInitializeComponent = true;

    DefaultCurrencyType = Currency::Default;
}

void UCurrencyManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CurrencyMap.Emplace(DefaultCurrencyType, 0);

    for (const auto& [CurrencyType, Amount] : StartupCurrencyMap)
    {
        CurrencyMap.Emplace(CurrencyType, Amount);
    }
}

void UCurrencyManagerComponent::SetCurrencyMap(const TMap<FGameplayTag, int64>& NewCurrencyMap)
{
    CurrencyMap = NewCurrencyMap;

    for (const auto& [CurrencyType, Amount] : StartupCurrencyMap)
    {
        OnUpdate.Broadcast(CurrencyType, Amount);
    }
}

int64 UCurrencyManagerComponent::GetCurrencyByType(FGameplayTag CurrencyType) const
{
    CheckCurrencyType(CurrencyType);

    const int64* CurrencyPtr = CurrencyMap.Find(CurrencyType);
    return CurrencyPtr ? *CurrencyPtr : 0;
}

bool UCurrencyManagerComponent::AddCurrencyByType(FGameplayTag CurrencyType, int64 Amount)
{
    CheckCurrencyType(CurrencyType);

    if (bool bCanAdd = Amount > 0 && CurrencyMap.Contains(CurrencyType); !bCanAdd) return false;

    SetCurrency(CurrencyType, GetCurrencyByType(CurrencyType) + Amount);

    return true;
}

bool UCurrencyManagerComponent::RemoveCurrencyByType(FGameplayTag CurrencyType, int64 Amount)
{
    CheckCurrencyType(CurrencyType);

    if (bool bCanRemove = Amount > 0 && GetCurrencyByType(CurrencyType) > Amount; !bCanRemove) return false;

    SetCurrency(CurrencyType, GetCurrencyByType(CurrencyType) - Amount);

    return true;
}

void UCurrencyManagerComponent::SetCurrency(FGameplayTag CurrencyType, int64 Amount)
{
    CurrencyMap.Emplace(CurrencyType, Amount);
    OnUpdate.Broadcast(CurrencyType, Amount);
}

void UCurrencyManagerComponent::CheckCurrencyType(FGameplayTag& CurrencyType) const
{
    if (CurrencyType == Currency::Default) CurrencyType = DefaultCurrencyType;
}
