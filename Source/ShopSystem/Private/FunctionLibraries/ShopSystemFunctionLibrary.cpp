// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ShopSystemFunctionLibrary.h"

#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/CustomerInterface.h"
#include "Interfaces/ProductInterface.h"

UDataAsset* UShopSystemFunctionLibrary::GetProductData(UObject* DataObject)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UProductInterface>(DataObject);
}

FGameplayTag UShopSystemFunctionLibrary::GetCurrencyType(UObject* DataObject)
{
    auto ProductData = GetProductData(DataObject);

    return ProductData ? IProductInterface::Execute_GetCurrencyType(ProductData) : FGameplayTag::EmptyTag;
}

int32 UShopSystemFunctionLibrary::GetBuyPrice(UObject* DataObject)
{
    auto ProductData = GetProductData(DataObject);

    return ProductData ? IProductInterface::Execute_GetBuyPrice(ProductData) : 0;
}

int32 UShopSystemFunctionLibrary::GetSellPrice(UObject* DataObject)
{
    auto ProductData = GetProductData(DataObject);

    return ProductData ? IProductInterface::Execute_GetSellPrice(ProductData) : 0;
}

bool UShopSystemFunctionLibrary::PurchaseProduct(const TScriptInterface<ICustomerInterface>& Customer,
                                                 const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    if (Customer && Quantity > 0)
    {
        if (auto ProductData = UShopSystemFunctionLibrary::GetProductData(Product.GetObject()))
        {
            const FGameplayTag CurrencyType = UShopSystemFunctionLibrary::GetCurrencyType(ProductData);
            const int32 BuyPrice = UShopSystemFunctionLibrary::GetBuyPrice(ProductData);

            // 구매 금액
            int32 TotalBuyPrice = Quantity * BuyPrice;

            // 소지금
            int32 Budget = ICustomerInterface::Execute_GetCurrency(Customer.GetObject(), CurrencyType);

            // 소지금 부족
            if (Budget < TotalBuyPrice) return false;

            // 소지금으로부터 구매 금액 차감 후 상품 지급
            ICustomerInterface::Execute_RemoveCurrency(Customer.GetObject(), CurrencyType, TotalBuyPrice);
            ICustomerInterface::Execute_AddProduct(Customer.GetObject(), Product, Quantity);

            return true;
        }
    }

    return false;
}
