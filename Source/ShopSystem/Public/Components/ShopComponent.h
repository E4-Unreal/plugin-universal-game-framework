// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"


class ICustomerInterface;
class IProductInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class SHOPSYSTEM_API UShopComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TScriptInterface<IProductInterface>> Products;

public:
    UShopComponent();

    UFUNCTION(BlueprintCallable)
    virtual bool Buy(const TScriptInterface<ICustomerInterface>& Customer, const TScriptInterface<IProductInterface>& Product);

    UFUNCTION(BlueprintCallable)
    virtual bool Sell(const TScriptInterface<ICustomerInterface>& Customer, const TScriptInterface<IProductInterface>& Product);
};
