// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DroppableWidgetBase.h"
#include "InventoryOutsideWidget.generated.h"

/**
 * 인벤토리 아이템 드랍을 위한 배경 위젯 클래스
 */
UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventoryOutsideWidget : public UDroppableWidgetBase
{
    GENERATED_BODY()

protected:
    /* UserWidget */

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    /* DraggableWidgetBase */

    virtual void OnWidgetDrop(UUserWidget* DropWidget) override;
};
