// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Types/UGFItem.h"
#include "UGFInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGFINVENTORYSYSTEM_API UUGFInventoryInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class UGFINVENTORYSYSTEM_API IUGFInventoryInterface
{
    GENERATED_BODY()

public:
    /**
     * @param Item 추가할 아이템의 종류 및 수량
     * @param Overflow 인벤토리 용량 부족으로 인해 추가하지 못한 아이템 수량
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void AddItem(const FUGFItem& Item, int32& Overflow);
    virtual void AddItem_Implementation(const FUGFItem& Item, int32& Overflow);

    /**
     * @param Item 제거할 아이템의 종류 및 수량
     * @param Underflow 인벤토리 보유 수량 부족으로 인해 제거하지 못한 아이템 수량
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void RemoveItem(const FUGFItem& Item, int32& Underflow);
    virtual void RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow);

    /**
     * @param Item 보유 여부를 확인하고자 하는 아이템의 종류 및 수량
     * @return
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool HasItem(const FUGFItem& Item) const;
    virtual bool HasItem_Implementation(const FUGFItem& Item) const;

    /**
     * 인벤토르 슬롯을 교체합니다.
     * 단, 두 슬롯 모두 동일한 아이템일 경우 TargetIndex 슬롯에 아이템이 중첩되어야 합니다.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SwapInventorySlot(int32 SelectedIndex, int32 TargetIndex);
    virtual void SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex);
};
