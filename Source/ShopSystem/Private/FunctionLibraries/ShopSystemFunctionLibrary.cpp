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
    if (Customer == nullptr || Product == nullptr || Quantity <= 0) return false;

    // 구매 금액
    int32 TotalBuyPrice = Quantity * IProductInterface::Execute_GetBuyPrice(Product.GetObject());

    // 소지금
    FGameplayTag CurrencyType = IProductInterface::Execute_GetCurrencyType(Product.GetObject());
    int32 Budget = ICustomerInterface::Execute_GetCurrency(Customer.GetObject(), CurrencyType);

    // 소지금 부족
    if (Budget < TotalBuyPrice) return false;

    // 소지금으로부터 구매 금액 차감 후 상품 지급
    ICustomerInterface::Execute_RemoveCurrency(Customer.GetObject(), CurrencyType, TotalBuyPrice);
    ICustomerInterface::Execute_AddProduct(Customer.GetObject(), Product, Quantity);

    return true;
}
