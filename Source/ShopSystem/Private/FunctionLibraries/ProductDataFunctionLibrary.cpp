// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ProductDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Interfaces/ProductInterface.h"

bool UProductDataFunctionLibrary::HasProductData(UDataDefinitionBase* Definition)
{
    return GetProductData(Definition) != nullptr;
}

FGameplayTag UProductDataFunctionLibrary::GetCurrencyType(UDataDefinitionBase* Definition)
{
    auto ProductData = GetProductData(Definition);

    return ProductData ? IProductInterface::Execute_GetCurrencyType(ProductData) : FGameplayTag::EmptyTag;
}

int32 UProductDataFunctionLibrary::GetBuyPrice(UDataDefinitionBase* Definition)
{
    auto ProductData = GetProductData(Definition);

    return ProductData ? IProductInterface::Execute_GetBuyPrice(ProductData) : 0;
}

int32 UProductDataFunctionLibrary::GetSellPrice(UDataDefinitionBase* Definition)
{
    auto ProductData = GetProductData(Definition);

    return ProductData ? IProductInterface::Execute_GetSellPrice(ProductData) : 0;
}

UDataAsset* UProductDataFunctionLibrary::GetProductData(UDataDefinitionBase* Definition)
{
    return Definition ? Definition->GetDataByInterface<UProductInterface>() : nullptr;
}
