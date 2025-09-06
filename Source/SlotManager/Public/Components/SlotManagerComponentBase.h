// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/ContentSlot.h"
#include "Components/ReplicatedComponent.h"
#include "SlotManagerComponentBase.generated.h"

class USlotContent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotUpdated, int32, Index);

/**
 * 인벤토리, 장비창, 스킬창, 퀵 슬롯 등의 부모 클래스
 */
UCLASS(Abstract)
class SLOTMANAGER_API USlotManagerComponentBase : public UReplicatedComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_Slots)
    TArray<FContentSlot> Slots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, TObjectPtr<USlotContent>> SlotMap;

public:
    UPROPERTY(BlueprintAssignable)
    FOnSlotUpdated OnSlotUpdated;

public:
    USlotManagerComponentBase();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual int32 GetMaxSlotNum() const { return 0; }

    UFUNCTION(BlueprintPure)
    virtual bool DoesSlotExist(int32 Index) const;

    UFUNCTION(BlueprintPure)
    virtual bool IsEmpty(int32 Index) const;

    UFUNCTION(BlueprintPure)
    virtual USlotContent* GetContent(int32 Index) const;

    UFUNCTION(BlueprintPure)
    virtual int32 GetEmptySlotIndex() const;

    UFUNCTION(BlueprintCallable)
    virtual void SetContent(int32 Index, USlotContent* NewContent);

    UFUNCTION(BlueprintCallable)
    virtual void AddContent(USlotContent* NewContent);

    UFUNCTION(BlueprintCallable)
    virtual void TransferContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex);

    UFUNCTION(BlueprintCallable)
    virtual void SwapContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex);

    UFUNCTION(BlueprintCallable)
    virtual void SyncContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex);

protected:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    virtual void CreateSlots();
    virtual void MappingSlots();
    virtual USlotContent* CreateContentFromData(UDataAsset* Data);
    virtual bool CheckContent(USlotContent* Content) const;
    virtual bool CheckContentClass(TSubclassOf<USlotContent> ContentClass) const;
    virtual bool CheckData(UDataAsset* Data) const;

    /* Replicate */

    UFUNCTION()
    virtual void OnRep_Slots(TArray<FContentSlot> OldSlots);
};
