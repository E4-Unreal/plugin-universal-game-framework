// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShopComponent.h"

#include "GameplayTagContainer.h"
#include "Interfaces/CustomerInterface.h"
#include "Interfaces/ProductInterface.h"


UShopComponent::UShopComponent()
{
}

bool UShopComponent::Buy(const TScriptInterface<ICustomerInterface>& Customer,
    const TScriptInterface<IProductInterface>& Product)
{
    if (bool bValid = Customer && Product; !bValid) return false;

    if (!Products.Contains(Product)) return false;

    const FGameplayTag CurrencyType = IProductInterface::Execute_GetCurrencyType(Product.GetObject());
    const int32 Budget = ICustomerInterface::Execute_GetCurrency(Customer.GetObject(), CurrencyType);
    const int32 BuyPrice = IProductInterface::Execute_GetBuyPrice(Product.GetObject());
    if (Budget < Product->GetBuyPrice()) return false;

    if (ICustomerInterface::Execute_AddProduct(Customer.GetObject(), Product))
    {
        ICustomerInterface::Execute_RemoveCurrency(Customer.GetObject(), CurrencyType, BuyPrice);
    }

    return true;
}

bool UShopComponent::Sell(const TScriptInterface<ICustomerInterface>& Customer,
    const TScriptInterface<IProductInterface>& Product)
{
    if (bool bValid = Customer && Product; !bValid) return false;

    const FGameplayTag CurrencyType = IProductInterface::Execute_GetCurrencyType(Product.GetObject());
    const int32 SellPrice = IProductInterface::Execute_GetSellPrice(Product.GetObject());

    if (ICustomerInterface::Execute_RemoveProduct(Customer.GetObject(), Product))
    {
        ICustomerInterface::Execute_AddCurrency(Customer.GetObject(), CurrencyType, SellPrice);
    }

    return true;
}
