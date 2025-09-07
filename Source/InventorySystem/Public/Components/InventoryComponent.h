// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SlotManagerComponentBase.h"
#include "InventoryComponent.generated.h"

class UItemInstance;

class IItemDataInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public USlotManagerComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TArray<TObjectPtr<UItemInstance>> StartupItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemActorInterface"))
    TSubclassOf<AActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FVector DropItemOffset;

public:
    UInventoryComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;

    /* SlotManagerComponentBase */

    virtual int32 GetMaxSlotNum() const override { return MaxSlotNum; }
    virtual bool HasContent(USlotContent* InContent) const override;
    virtual bool AddContent(USlotContent* InContent) override;
    virtual bool RemoveContent(USlotContent* InContent) override;
    virtual void SwapContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void AddItemFromData(UDataAsset* NewData, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable)
    virtual bool SetSlotQuantity(int32 SlotIndex, int32 NewQuantity);

    UFUNCTION(BlueprintCallable)
    virtual void DropItemFromSlot(int32 SlotIndex, int32 Quantity);

    /* Getter */

    // 현재 아이템 보유 수량
    UFUNCTION(BlueprintPure)
    virtual int32 GetItemQuantity(UDataAsset* Item) const;

    // 현재 추가 가능한 아이템 수량
    UFUNCTION(BlueprintPure)
    virtual int32 GetItemCapacity(UDataAsset* Item) const;

protected:
    virtual void AddDefaultItems();
};
