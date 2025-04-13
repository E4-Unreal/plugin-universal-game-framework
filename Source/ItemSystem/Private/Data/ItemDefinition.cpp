// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

#include "Data/ItemConfig.h"
#include "Types/ItemDataTableRow.h"

bool UItemDefinition::IsValid() const
{
    return Super::IsValid() && Data.IsValid();
}

const UItemConfig* UItemDefinition::GetItemConfigByClass(const TSubclassOf<UItemConfig> ItemConfigClass)
{
    if (ItemConfigClass == nullptr) return nullptr;

    UItemConfig* FoundItemConfig = nullptr;

    for (auto ItemConfig : ItemConfigs)
    {
        if (ItemConfig && ItemConfig->IsA(ItemConfigClass) && ItemConfig->IsValid())
        {
            FoundItemConfig = ItemConfig;
            break;
        }
    }

    return FoundItemConfig;
}

const UItemConfig* UItemDefinition::GetItemConfigByInterface(const TSubclassOf<UInterface> Interface)
{
    if (Interface == nullptr) return nullptr;

    UItemConfig* FoundItemConfig = nullptr;

    for (auto ItemConfig : ItemConfigs)
    {
        if (ItemConfig && ItemConfig->GetClass()->ImplementsInterface(Interface) && ItemConfig->IsValid())
        {
            FoundItemConfig = ItemConfig;
            break;
        }
    }

    return FoundItemConfig;
}

void UItemDefinition::OnUpdate(FTableRowBase* TableRow)
{
    if (FItemDataTableRow* ItemDataTableRow = static_cast<FItemDataTableRow*>(TableRow))
    {
        FItemDefinitionData NewData
        {
            ItemDataTableRow->DisplayText
        };

        if (Data != NewData)
        {
            Data = NewData;
            MarkPackageDirty();
        }
    }
}

void UItemDefinition::OnReset()
{
    Data = FItemDefinitionData::EmptyData;
    ItemConfigs.Reset();
}
