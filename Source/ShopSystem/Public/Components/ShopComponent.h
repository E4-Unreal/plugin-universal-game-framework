// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"

class UDataInstanceBase;
class UDataDefinitionBase;

USTRUCT(BlueprintType)
struct FProductSlot
{
    GENERATED_BODY()

    static const FProductSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UDataDefinitionBase> Definition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 Stock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 MaxStock;

    FProductSlot() { }
};

UCLASS(meta = (BlueprintSpawnableComponent))
class SHOPSYSTEM_API UShopComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FProductSlot> Slots;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, int32> SlotIndexMap;

public:
    UShopComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;

    /* Query */

    UFUNCTION(BlueprintPure)
    bool IsSlotExist(int32 Index) const { return SlotIndexMap.Contains(Index); }

    UFUNCTION(BlueprintPure)
    const FProductSlot& GetSlot(int32 Index) const;

    /* API */

    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Customer"))
    virtual bool BuyProduct(AActor* Customer, int32 Index, int32 Quantity);

    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Customer"))
    virtual bool SellProduct(AActor* Customer, UDataDefinitionBase* Definition, int32 Quantity);

protected:
    virtual bool CheckDefinition(UDataDefinitionBase* Definition) const;
    virtual bool CheckInstance(UDataInstanceBase* Instance) const;
    virtual void SetStock(int32 Index, int32 NewStock);
};
