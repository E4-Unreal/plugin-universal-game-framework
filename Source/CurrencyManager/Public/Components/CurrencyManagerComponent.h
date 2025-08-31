// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CurrencyManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCurrencyUpdateDelegate, const FGameplayTag&, CurrencyType, int64, Amount);

UCLASS(meta = (BlueprintSpawnableComponent))
class CURRENCYMANAGER_API UCurrencyManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FCurrencyUpdateDelegate OnUpdate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Currency"))
    FGameplayTag DefaultCurrencyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Currency"))
    TMap<FGameplayTag, int64> StartupCurrencyMap;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, int64> CurrencyMap;

public:
    UCurrencyManagerComponent();

    virtual void InitializeComponent() override;

    UFUNCTION(BlueprintCallable)
    void SetCurrencyMap(const TMap<FGameplayTag, int64>& NewCurrencyMap);

    UFUNCTION(BlueprintPure)
    const TMap<FGameplayTag, int64>& GetCurrencyMap() const { return CurrencyMap; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE int64 GetCurrency() const { return GetCurrencyByType(DefaultCurrencyType); }

    UFUNCTION(BlueprintPure)
    virtual int64 GetCurrencyByType(FGameplayTag CurrencyType) const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool HasCurrency(int64 Amount) const { return HasCurrencyByType(DefaultCurrencyType, Amount); }

    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool HasCurrencyByType(FGameplayTag CurrencyType, int64 Amount) const { return GetCurrencyByType(CurrencyType) >= Amount; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool AddCurrency(int64 Amount) { return AddCurrencyByType(DefaultCurrencyType, Amount); }

    UFUNCTION(BlueprintCallable)
    virtual bool AddCurrencyByType(FGameplayTag CurrencyType, int64 Amount);

    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool RemoveCurrency(int64 Amount) { return RemoveCurrencyByType(DefaultCurrencyType, Amount); }

    UFUNCTION(BlueprintCallable)
    virtual bool RemoveCurrencyByType(FGameplayTag CurrencyType, int64 Amount);

protected:
    virtual void SetCurrency(FGameplayTag CurrencyType, int64 Amount);

    void CheckCurrencyType(FGameplayTag& CurrencyType) const;
};
