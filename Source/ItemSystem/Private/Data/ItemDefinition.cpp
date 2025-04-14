// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

#include "Data/ItemConfig.h"
#include "Types/ItemDataTableRow.h"

const FInstancedStruct UItemDefinition::EmptyData;

bool UItemDefinition::IsValid() const
{
    return Super::IsValid() && !DisplayText.IsEmpty();
}

bool UItemDefinition::HasData(const UScriptStruct* StructType) const
{
    for (const auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType))
        {
            return true;
        }
    }

    return false;
}

const FInstancedStruct& UItemDefinition::GetData(const UScriptStruct* StructType) const
{
    for (const auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType))
        {
            return Data;
        }
    }

    return EmptyData;
}

void UItemDefinition::SetData(const FInstancedStruct& Value)
{
    const UScriptStruct* StructType = Value.GetScriptStruct();
    for (auto& Data : DataList)
    {
        if (Data.GetScriptStruct()->IsChildOf(StructType))
        {
            Data = Value;
            return;
        }
    }

    DataList.Emplace(Value);
}

UItemConfig* UItemDefinition::GetItemConfigByClass(const TSubclassOf<UItemConfig> ItemConfigClass)
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

UItemConfig* UItemDefinition::GetItemConfigByInterface(const TSubclassOf<UInterface> Interface)
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
        if (!DisplayText.IdenticalTo(ItemDataTableRow->DisplayText))
        {
            DisplayText = ItemDataTableRow->DisplayText;
            MarkPackageDirty();
        }
    }

    // Delete ItemConfigs
    for (int32 Index = ItemConfigs.Num() - 1; Index >= 0; --Index)
    {
        if (ItemConfigs[Index]->IsNotValid())
        {
            ItemConfigs.RemoveAt(Index);
        }
    }

    UpdateItemConfigs(TableRow);
}

void UItemDefinition::OnReset()
{
    DisplayText = FText::GetEmpty();
    ItemConfigs.Reset();
}

UItemConfig* UItemDefinition::GetOrCreateItemConfig(TSubclassOf<UItemConfig> ItemConfigClass)
{
    UItemConfig* ItemConfig = GetItemConfigByClass(ItemConfigClass);
    if (ItemConfig == nullptr)
    {
        ItemConfig = NewObject<UItemConfig>(this, ItemConfigClass);
        ItemConfigs.Emplace(ItemConfig);
        MarkPackageDirty();
    }

    return ItemConfig;
}

void UItemDefinition::UpdateItemConfigs(FTableRowBase* TableRow)
{
    /**
     * if(FProjectItemDataTableRow* ProjectItemDataTableRow = static_cast<FProjectItemDataTableRow*>(TableRow))
     * {
     *   FInventoryItemData InventoryItemData
     *   {
     *      ProjectItemDataTableRow->MaxStack,
     *      ProjectItemDataTableRow->Thumbnail,
     *      ...
     *   };
     *   UInventoryItemConfig* InventoryItemConfig = GetOrCreateItemConfig<UInventoryItemConfig>();
     *   InventoryItemConfig->Update(InventoryItemData);
     * }
     */
}
