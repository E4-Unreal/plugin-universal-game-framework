// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShopComponent.h"

#include "Components/CurrencyManagerComponent.h"
#include "Components/InventoryComponent.h"
#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "FunctionLibraries/WeaponDataFunctionLibrary.h"

const FProductSlot FProductSlot::EmptySlot;

UShopComponent::UShopComponent()
{
}

void UShopComponent::BeginPlay()
{
    Super::BeginPlay();

    for (int32 Index = 0; Index < Slots.Num(); ++Index)
    {
        const auto& Product = Slots[Index];
        if (CheckDefinition(Product.Definition) && Product.MaxStock > 0)
        {
            SlotIndexMap.Emplace(SlotIndexMap.Num(), Index);
        }
    }
}

const FProductSlot& UShopComponent::GetSlot(int32 Index) const
{
    if (SlotIndexMap.Contains(Index))
    {
        return Slots[Index];
    }

    return FProductSlot::EmptySlot;
}

bool UShopComponent::BuyItem(AActor* Customer, int32 Index, int32 Quantity)
{
    // 입력 유효성 확인
    if (Customer && IsSlotExist(Index) && Quantity > 0)
    {
        // 재고 수량 확인
        const auto& Slot = GetSlot(Index);
        if (Slot.Stock >= Quantity)
        {
            // 컴포넌트 확인
            auto CurrencyManager = Customer->GetComponentByClass<UCurrencyManagerComponent>();
            auto Inventory = Customer->GetComponentByClass<UInventoryComponent>();
            if (CurrencyManager && Inventory)
            {
                // 구매 금액 계산
                auto Definition = Slot.Definition;
                const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Definition);
                const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Definition);
                const int32 TotalBuyPrice = BuyPrice * Quantity;

                // 구매 가능 여부 확인
                if (CurrencyManager->HasCurrencyByType(CurrencyType, TotalBuyPrice))
                {
                    // 인벤토리에 아이템 추가
                    if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Definition))
                    {
                        UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
                        if (Inventory->AddContent(ItemInstance))
                        {
                            // 구매 금액 차감
                            CurrencyManager->RemoveCurrencyByType(CurrencyType, TotalBuyPrice);

                            // 재고 수량 차감
                            SetStock(Index, Slot.Stock - Quantity);

                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool UShopComponent::SellItem(AActor* Customer, UDataDefinitionBase* Definition, int32 Quantity)
{
    // 입력 유효성 검사
    if (Customer && CheckDefinition(Definition))
    {
        // 판매 금액 계산
        const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Definition);
        const int32 SellPrice = UProductDataFunctionLibrary::GetSellPrice(Definition);
        const int32 TotalSellPrice = SellPrice * Quantity;

        // 컴포넌트 확인
        auto CurrencyManager = Customer->GetComponentByClass<UCurrencyManagerComponent>();
        auto Inventory = Customer->GetComponentByClass<UInventoryComponent>();
        if (CurrencyManager && Inventory)
        {
            // 인벤토리 수량 확인
            if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Definition))
            {
                UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
                if (Inventory->HasContent(ItemInstance))
                {
                    // 인벤토리 수량 차감
                    if (Inventory->RemoveContent(ItemInstance))
                    {
                        // 판매 금액 지불
                        CurrencyManager->RemoveCurrencyByType(CurrencyType, TotalSellPrice);

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool UShopComponent::SellEquipment(AActor* Customer, UDataInstanceBase* Instance)
{
    // 입력 유효성 검사
    if (Customer && CheckInstance(Instance))
    {
        // 판매 금액 계산
        auto Definition = Instance->Definition;
        const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Definition);
        int32 SellPrice = UProductDataFunctionLibrary::GetSellPrice(Definition);
        if (UWeaponDataFunctionLibrary::HasWeaponInstance(Instance))
        {
            const float MaxDurability = UWeaponDataFunctionLibrary::GetMaxDurability(Definition);
            const float Durability = UWeaponDataFunctionLibrary::GetDurability(Instance);

            if (MaxDurability >= 0.0f)
            {
                const float DurabilityRatio = Durability / MaxDurability;
                SellPrice *= DurabilityRatio;
            }
        }

        // 컴포넌트 확인
        auto CurrencyManager = Customer->GetComponentByClass<UCurrencyManagerComponent>();
        auto Inventory = Customer->GetComponentByClass<UInventoryComponent>();
        if (CurrencyManager && Inventory)
        {
            // 인벤토리 수량 확인
            if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Definition))
            {
                UItemDataFunctionLibrary::SetQuantity(ItemInstance, 1);
                if (Inventory->HasContent(ItemInstance))
                {
                    // 인벤토리 수량 차감
                    if (Inventory->RemoveContent(ItemInstance))
                    {
                        // 판매 금액 지불
                        CurrencyManager->RemoveCurrencyByType(CurrencyType, SellPrice);

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool UShopComponent::CheckDefinition(UDataDefinitionBase* Definition) const
{
    return Definition && UProductDataFunctionLibrary::HasProductData(Definition);
}

bool UShopComponent::CheckInstance(UDataInstanceBase* Instance) const
{
    return Instance && CheckDefinition(Instance->Definition);
}

void UShopComponent::SetStock(int32 Index, int32 NewStock)
{
    if (IsSlotExist(Index))
    {
        auto& Slot = const_cast<FProductSlot&>(GetSlot(Index));
        Slot.Stock = FMath::Clamp(NewStock, 0, Slot.MaxStock);
    }
}
