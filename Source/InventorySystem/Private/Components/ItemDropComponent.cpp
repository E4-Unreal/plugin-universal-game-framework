// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemDropComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Components/InventoryComponent.h"
#include "Data/ItemDropConfig.h"
#include "Interfaces/DataInterface.h"
#include "Interfaces/ItemInstanceInterface.h"
#include "Settings/InventorySystemSettings.h"

UItemDropComponent::UItemDropComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    bAutoDestroy = true;

    SpawnOffset = FVector(0, 0, 50);
    ImpulseAngle = 90;
    ImpulseStrength = 1000;
}

bool UItemDropComponent::AddItemsToInventory(AActor* TargetActor)
{
    if (auto InventoryComponent = TargetActor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& Item : GetItems())
        {
            if (Item) InventoryComponent->AddContent(Item);
        }

        if (bAutoDestroy) GetOwner()->Destroy();

        return true;
    }

    return false;
}

bool UItemDropComponent::DropItems()
{
    if (auto LocalItemActorClass = GetItemActorClass())
    {
        const auto& Items = GetItems();
        if (!Items.IsEmpty())
        {
            const auto& SpawnedItemActors = UInventorySystemFunctionLibrary::SpawnItemActors(GetOwner(), LocalItemActorClass, Items, SpawnOffset);
            for (const auto& SpawnedItemActor : SpawnedItemActors)
            {
                UInventorySystemFunctionLibrary::ImpulseActor(SpawnedItemActor, ImpulseAngle, ImpulseStrength);
            }

            if (bAutoDestroy) GetOwner()->Destroy();

            return true;
        }
    }

    return false;
}

UItemDropConfig* UItemDropComponent::GetDropConfig() const
{
    return DropConfigInstance ? DropConfigInstance : DropConfig;
}

TArray<UObject*> UItemDropComponent::GetItems() const
{
    TArray<UObject*> Items;
    if (auto LocalDropConfig = GetDropConfig())
    {
        const auto& DropDataList = LocalDropConfig->GetDataList();
        for (const auto& DropData : DropDataList)
        {
            const auto& ItemData = DropData.ItemData;
            const auto& DropChance = DropData.DropChance;
            const auto& CountChanceMap = DropData.CountChanceMap;

            // 아이템 드랍 확률 검사
            if (ItemData && ItemData->Implements<UDataInterface>() && FMath::RandRange(0.0f, 1.0f) <= DropChance)
            {
                // 아이템 드랍 개수 확률 검사
                float TotalChance = 0.0f;
                for (const auto& [Count, Chance] : CountChanceMap)
                {
                    TotalChance += Chance;
                }

                float Random = FMath::RandRange(0.0f, TotalChance);
                float AccumulatedChance = 0.0f;
                int32 ItemCount = 0;
                for (const auto& [Count, Chance] : CountChanceMap)
                {
                    AccumulatedChance += Chance;
                    if (Random <= AccumulatedChance)
                    {
                        ItemCount = Count;
                        break;
                    }
                }


                if (ItemCount > 0)
                {
                    UObject* NewItem = IDataInterface::Execute_CreateInstanceData(ItemData);
                    if (NewItem && NewItem->Implements<UItemInstanceInterface>())
                    {
                        IItemInstanceInterface::Execute_SetQuantity(NewItem, ItemCount);

                        Items.Emplace(NewItem);
                    }
                }
            }
        }
    }

    return Items;
}

TSubclassOf<AActor> UItemDropComponent::GetItemActorClass() const
{
    return ItemActorClass ? ItemActorClass : UInventorySystemSettings::Get()->GetDefaultItemActorClass();
}
