// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "InventoryOutsideWidget.generated.h"

/**
 * 인벤토리 아이템 드랍을 위한 배경 위젯 클래스
 */
UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventoryOutsideWidget : public UInventoryWidgetBase
{
    GENERATED_BODY()

protected:
    virtual void OnInventorySlotWidgetDrop(UInventorySlotWidgetBase* InventorySlotWidget) override;
};
