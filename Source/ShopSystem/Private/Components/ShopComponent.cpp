// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShopComponent.h"

#include "Components/CurrencyManagerComponent.h"
#include "Components/InventoryComponent.h"
#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "FunctionLibraries/WeaponDataFunctionLibrary.h"
#include "Types/Currency.h"

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

TArray<FProductSlot> UShopComponent::GetSlots() const
{
    TArray<FProductSlot> ValidSlots;
    for (const auto& [Index, SlotIndex] : SlotIndexMap)
    {
        if (SlotIndex < Slots.Num())
        {
            ValidSlots.Emplace(Slots[SlotIndex]);
        }
    }

    return ValidSlots;
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
        auto Item = Slot.Definition;
        const int32 Stock = Slot.Stock;

        if (Stock >= Quantity)
        {
            // 구매 금액 계산
            const FCurrency BuyPrice = CalculateBuyPrice(Item, Quantity);

            // 구매 가능 여부 확인
            if (HasCurrency(Customer, BuyPrice))
            {
                // 인벤토리에 아이템 추가
                if (AddItem(Customer, Item, Quantity))
                {
                    // 구매 금액 차감
                    RemoveCurrency(Customer, BuyPrice);

                    // 재고 수량 차감
                    SetStock(Index, Stock - Quantity);

                    return true;
                }
            }
        }
    }

    return false;
}

bool UShopComponent::SellItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity)
{
    // 입력 유효성 검사
    if (Customer && CheckDefinition(Item))
    {
        // 판매 금액 계산
        const FCurrency SellPrice = CalculateSellPrice(Item, Quantity);

        // 인벤토리 수량 확인
        if (HasItem(Customer, Item, Quantity))
        {
            // 인벤토리 수량 차감
            if (RemoveItem(Customer, Item, Quantity))
            {
                // 판매 금액 지불
                AddCurrency(Customer, SellPrice);

                return true;
            }
        }
    }

    return false;
}

bool UShopComponent::SellEquipment(AActor* Customer, UDataInstanceBase* Equipment)
{
    // 입력 유효성 검사
    if (Customer && CheckInstance(Equipment))
    {
        // 판매 금액 계산
        const FCurrency SellPrice = CalculateEquipmentSellPrice(Equipment);

        // 인벤토리 수량 확인
        if (HasEquipment(Customer, Equipment))
        {
            // 인벤토리 수량 차감
            if (RemoveEquipment(Customer, Equipment))
            {
                // 판매 금액 지불
                AddCurrency(Customer, SellPrice);

                return true;
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

bool UShopComponent::HasCurrency(AActor* Customer, FCurrency Currency) const
{
    if (Customer)
    {
        if (auto CurrencyManager = Customer->GetComponentByClass<UCurrencyManagerComponent>())
        {
            return CurrencyManager->HasCurrencyByType(Currency.CurrencyType, Currency.Amount);
        }
    }

    return false;
}

bool UShopComponent::AddCurrency(AActor* Customer, FCurrency Currency) const
{
    if (Customer)
    {
        if (auto CurrencyManager = Customer->GetComponentByClass<UCurrencyManagerComponent>())
        {
            return CurrencyManager->AddCurrencyByType(Currency.CurrencyType, Currency.Amount);
        }
    }

    return false;
}

bool UShopComponent::RemoveCurrency(AActor* Customer, FCurrency Currency) const
{
    if (Customer)
    {
        if (auto CurrencyManager = Customer->GetComponentByClass<UCurrencyManagerComponent>())
        {
            return CurrencyManager->RemoveCurrencyByType(Currency.CurrencyType, Currency.Amount);
        }
    }

    return false;
}

bool UShopComponent::HasItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity) const
{
    if (Customer)
    {
        if (auto Inventory = Customer->GetComponentByClass<UInventoryComponent>())
        {
            if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Item))
            {
                UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
                return Inventory->HasContent(ItemInstance);
            }
        }
    }

    return false;
}

bool UShopComponent::AddItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity) const
{
    if (Customer)
    {
        if (auto Inventory = Customer->GetComponentByClass<UInventoryComponent>())
        {
            if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Item))
            {
                UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
                return Inventory->AddContent(ItemInstance);
            }
        }
    }

    return false;
}

bool UShopComponent::RemoveItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity) const
{
    if (Customer)
    {
        if (auto Inventory = Customer->GetComponentByClass<UInventoryComponent>())
        {
            if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Item))
            {
                UItemDataFunctionLibrary::SetQuantity(ItemInstance, Quantity);
                return Inventory->RemoveContent(ItemInstance);
            }
        }
    }

    return false;
}

FCurrency UShopComponent::CalculateBuyPrice(UDataDefinitionBase* Item, int32 Quantity) const
{
    const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Item);
    const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Item);
    const int32 TotalBuyPrice = BuyPrice * Quantity;

    return FCurrency(CurrencyType, TotalBuyPrice);
}

FCurrency UShopComponent::CalculateSellPrice(UDataDefinitionBase* Item, int32 Quantity) const
{
    const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Item);
    const int32 SellPrice = UProductDataFunctionLibrary::GetSellPrice(Item);
    const int32 TotalSellPrice = SellPrice * Quantity;

    return FCurrency(CurrencyType, TotalSellPrice);
}

bool UShopComponent::HasEquipment(AActor* Customer, UDataInstanceBase* Equipment) const
{
    if (Customer)
    {
        if (auto Inventory = Customer->GetComponentByClass<UInventoryComponent>())
        {
            return Inventory->HasContent(Equipment);
        }
    }

    return false;
}

bool UShopComponent::RemoveEquipment(AActor* Customer, UDataInstanceBase* Equipment) const
{
    if (Customer)
    {
        if (auto Inventory = Customer->GetComponentByClass<UInventoryComponent>())
        {
            return Inventory->RemoveContent(Equipment);
        }
    }

    return false;
}

FCurrency UShopComponent::CalculateEquipmentSellPrice(UDataInstanceBase* Equipment) const
{
    auto Item = Equipment->Definition;
    const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Item);
    int32 SellPrice = UProductDataFunctionLibrary::GetSellPrice(Item);
    if (UWeaponDataFunctionLibrary::HasWeaponInstance(Equipment))
    {
        const float MaxDurability = UWeaponDataFunctionLibrary::GetMaxDurability(Item);
        const float Durability = UWeaponDataFunctionLibrary::GetDurability(Equipment);

        if (MaxDurability >= 0.0f)
        {
            const float DurabilityRatio = Durability / MaxDurability;
            SellPrice *= DurabilityRatio;
        }
    }

    return FCurrency(CurrencyType, SellPrice);
}

void UShopComponent::SetStock(int32 Index, int32 NewStock)
{
    if (IsSlotExist(Index))
    {
        auto& Slot = const_cast<FProductSlot&>(GetSlot(Index));
        if (!Slot.bInfiniteStock) Slot.Stock = FMath::Clamp(NewStock, 0, Slot.MaxStock);
    }
}
