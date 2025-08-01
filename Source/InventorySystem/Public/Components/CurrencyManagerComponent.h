// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CurrencyManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UCurrencyManagerComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Currency"))
    TMap<FGameplayTag, int32> DefaultCurrencies;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, int32> CurrencyMap;

public:
    UCurrencyManagerComponent();

    virtual void InitializeComponent() override;

    UFUNCTION(BlueprintPure)
    virtual int32 GetCurrency(const FGameplayTag& CurrencyType) const;

    UFUNCTION(BlueprintPure)
    virtual bool HasCurrency(const FGameplayTag& CurrencyType, int32 Amount) const { return GetCurrency(CurrencyType) >= Amount; }

    UFUNCTION(BlueprintCallable)
    virtual bool AddCurrency(const FGameplayTag& CurrencyType, int32 Amount);

    UFUNCTION(BlueprintCallable)
    virtual bool RemoveCurrency(const FGameplayTag& CurrencyType, int32 Amount);
};
