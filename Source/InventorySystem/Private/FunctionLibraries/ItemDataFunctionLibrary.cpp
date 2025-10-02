// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/ItemDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/ItemInstanceInterface.h"


bool UItemDataFunctionLibrary::HasItemData(UDataDefinitionBase* Definition)
{
    return GetItemData(Definition) != nullptr;
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

bool UItemDataFunctionLibrary::HasItemInstance(UDataInstanceBase* Instance)
{
    return GetItemInstance(Instance) != nullptr;
}

int32 UItemDataFunctionLibrary::GetQuantity(UDataInstanceBase* Instance)
{
    auto ItemInstance = GetItemInstance(Instance);

    return ItemInstance ? IItemInstanceInterface::Execute_GetQuantity(ItemInstance) : 0;
}

void UItemDataFunctionLibrary::SetQuantity(UDataInstanceBase* Instance, int32 NewQuantity)
{
    if (auto ItemInstance = GetItemInstance(Instance))
    {
        IItemInstanceInterface::Execute_SetQuantity(ItemInstance, NewQuantity);
    }
}

UDataAsset* UItemDataFunctionLibrary::GetItemData(UDataDefinitionBase* Definition)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UItemDataInterface>(Definition);
}

UObject* UItemDataFunctionLibrary::GetItemInstance(UDataInstanceBase* Instance)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UItemInstanceInterface>(Instance);
}
