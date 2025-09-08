// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/ContentSlot.h"
#include "Components/ReplicatedComponent.h"
#include "SlotManagerComponentBase.generated.h"

class USlotContent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSlotUpdated, int32, Index, USlotContent*, OldContent, USlotContent*, NewContent);

/**
 * 인벤토리, 장비창, 스킬창, 퀵 슬롯 등의 부모 클래스
 */
UCLASS(Abstract)
class SLOTMANAGER_API USlotManagerComponentBase : public UReplicatedComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UInterface>> UsingDataInterfaces;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UInterface>> UsingInstanceInterfaces;

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
    virtual bool IsSlotEmpty(int32 Index) const;

    UFUNCTION(BlueprintPure)
    virtual bool HasContent(USlotContent* InContent) const;

    UFUNCTION(BlueprintPure)
    virtual USlotContent* GetContent(int32 Index) const;

    UFUNCTION(BlueprintPure)
    virtual int32 GetEmptySlotIndex(USlotContent* NewContent) const;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    virtual void SetContent(int32 Index, USlotContent* NewContent);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    virtual bool AddContent(USlotContent* NewContent);

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    virtual bool AddContentByData(UDataAsset* NewData) { return AddContent(CreateContentFromData(NewData)); }

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    virtual bool RemoveContent(USlotContent* InContent);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    virtual void TransferContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    virtual void SwapContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    virtual void SyncContent(USlotManagerComponentBase* Source, int32 SourceIndex, USlotManagerComponentBase* Destination, int32 DestinationIndex);

protected:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    virtual void CreateSlots();
    virtual void MappingSlots();
    virtual USlotContent* CreateContentFromData(UDataAsset* Data) const;
    virtual bool CheckContent(USlotContent* Content) const;
    virtual bool CheckData(UDataAsset* Data) const;

    UFUNCTION()
    virtual void HandleOnSlotUpdated(int32 Index, USlotContent* OldContent, USlotContent* NewContent);

    /* Replicate */

    UFUNCTION()
    virtual void OnRep_Slots(TArray<FContentSlot> OldSlots);
};
