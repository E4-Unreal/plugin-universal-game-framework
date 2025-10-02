// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ShopSystemFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "Interfaces/CustomerInterface.h"
#include "Interfaces/ProductDataInterface.h"

bool UShopSystemFunctionLibrary::PurchaseProduct(AActor* Customer, UDataDefinitionBase* Product, int32 Quantity)
{
    if (Customer && Quantity > 0)
    {
        if (UProductDataFunctionLibrary::HasProductData(Product))
        {
            const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Product);
            const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Product);

            // 구매 금액
            int32 TotalBuyPrice = Quantity * BuyPrice;

            // 소지금
            int32 Budget = ICustomerInterface::Execute_GetCurrency(Customer, CurrencyType);

            // 소지금 부족
            if (Budget < TotalBuyPrice) return false;

            // 소지금으로부터 구매 금액 차감 후 상품 지급
            ICustomerInterface::Execute_RemoveCurrency(Customer, CurrencyType, TotalBuyPrice);
            ICustomerInterface::Execute_AddProduct(Customer, Product, Quantity);

            return true;
        }
    }

    return false;
}
