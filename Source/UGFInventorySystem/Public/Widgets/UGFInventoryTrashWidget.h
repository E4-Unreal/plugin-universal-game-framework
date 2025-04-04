// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGFInventoryTrashWidget.generated.h"

class UUGFInventoryComponent;

/**
 * 인벤토리 아이템 삭제 전용 위젯
 */
UCLASS(Abstract)
class UGFINVENTORYSYSTEM_API UUGFInventoryTrashWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(Transient)
    TObjectPtr<UUGFInventoryComponent> InventoryComponent;

protected:
    virtual void NativeOnInitialized() override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
