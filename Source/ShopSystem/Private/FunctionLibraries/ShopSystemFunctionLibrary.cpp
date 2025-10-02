// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ShopSystemFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "Interfaces/CustomerInterface.h"
#include "Interfaces/ProductInterface.h"

bool UShopSystemFunctionLibrary::PurchaseProduct(const TScriptInterface<ICustomerInterface>& Customer,
                                                 const TScriptInterface<IProductInterface>& Product, int32 Quantity)
{
    if (Customer && Quantity > 0)
    {
        if (auto Definition = Cast<UDataDefinitionBase>(Product.GetObject()))
        {
            if (UProductDataFunctionLibrary::HasProductData(Definition))
            {
                const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Definition);
                const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Definition);

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
    }

    return false;
}
