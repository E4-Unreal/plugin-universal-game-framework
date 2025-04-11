// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemConfig.h"

bool UItemConfig::Update(UItemDefinition* ItemDefinition, FItemDataTableRow* Row)
{
    if (ItemDefinition == nullptr || Row == nullptr)
    {
        bValid = false;
        return false;
    }

    bValid = true;

    return OnUpdate(ItemDefinition, Row);
}

bool UItemConfig::OnUpdate(UItemDefinition* ItemDefinition, FItemDataTableRow* Row)
{
    return true;
}
