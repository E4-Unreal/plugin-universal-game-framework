// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinition.h"

#include "Data/UGFItemConfig.h"

bool UUGFItemDefinition::IsValid() const
{
    for (const auto& ItemConfig : Data.ItemConfigs)
    {
        if (!ItemConfig->IsValid()) return false;
    }

    return true;
}
