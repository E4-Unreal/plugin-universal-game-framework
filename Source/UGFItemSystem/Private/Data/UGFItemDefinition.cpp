// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinition.h"

#include "Data/UGFItemConfig.h"

template <typename T>
const T* UUGFItemDefinition::FindItemConfigByClass(TSubclassOf<T> ItemConfigClass) const
{
    if (ItemConfigClass == nullptr || !ItemConfigClass->IsChildOf(UUGFItemConfig::StaticClass())) return nullptr;

    for (auto ItemConfig : Data.ItemConfigs)
    {
        if (ItemConfig && ItemConfig->IsA(ItemConfigClass))
        {
            return Cast<T>(ItemConfig);
        }
    }

    return nullptr;
}
