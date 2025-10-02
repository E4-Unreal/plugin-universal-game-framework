// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ItemDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/ItemInstanceInterface.h"


UDataAsset* UItemDataFunctionLibrary::GetItemData(UDataDefinitionBase* Definition)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UItemDataInterface>(Definition);
}

int32 UItemDataFunctionLibrary::GetMaxStack(UDataDefinitionBase* Definition)
{
    auto ItemData = GetItemData(Definition);

    return ItemData ? IItemDataInterface::Execute_GetMaxStack(ItemData) : 0;
}

FGameplayTag UItemDataFunctionLibrary::GetItemType(UDataDefinitionBase* Definition)
{
    auto ItemData = GetItemData(Definition);

    return ItemData ? IItemDataInterface::Execute_GetItemType(ItemData) : FGameplayTag::EmptyTag;
}

UDataInstanceBase* UItemDataFunctionLibrary::CreateItemInstance(UDataDefinitionBase* Definition)
{
    if (Definition)
    {
        auto DataInstance = UDataManagerFunctionLibrary::CreateDataInstance(Definition);
        auto ItemInstance = GetItemInstance(DataInstance);

        return ItemInstance ? DataInstance : nullptr;
    }

    return nullptr;
}

UObject* UItemDataFunctionLibrary::GetItemInstance(UDataInstanceBase* DataInstance)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UItemInstanceInterface>(DataInstance);
}

int32 UItemDataFunctionLibrary::GetQuantity(UDataInstanceBase* DataInstance)
{
    auto ItemInstance = GetItemInstance(DataInstance);

    return ItemInstance ? IItemInstanceInterface::Execute_GetQuantity(ItemInstance) : 0;
}

void UItemDataFunctionLibrary::SetQuantity(UDataInstanceBase* DataInstance, int32 NewQuantity)
{
    if (auto ItemInstance = GetItemInstance(DataInstance))
    {
        IItemInstanceInterface::Execute_SetQuantity(ItemInstance, NewQuantity);
    }
}
