// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShopComponent.h"

#include "Components/CurrencyManagerComponent.h"
#include "Components/InventoryComponent.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"

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
        if (Product.Definition && Product.MaxStock > 0)
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

bool UShopComponent::BuyProduct(AActor* Customer, int32 Index, int32 Quantity)
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
                            // 구매 비용 차감
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

void UShopComponent::SetStock(int32 Index, int32 NewStock)
{
    if (IsSlotExist(Index))
    {
        auto& Slot = const_cast<FProductSlot&>(GetSlot(Index));
        Slot.Stock = FMath::Clamp(NewStock, 0, Slot.MaxStock);
    }
}
