// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataManagerSubsystem.generated.h"

class USaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveGameDelegate, USaveGame*, SaveGame);

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FSaveGameDelegate OnSaveDataDelegate;

    UPROPERTY(BlueprintAssignable)
    FSaveGameDelegate OnLoadDataDelegate;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString DefaultSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<USaveGame> SaveGameClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<USaveGame> SaveGame;

public:
    UDataManagerSubsystem();

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintCallable)
    virtual void SaveData() { SaveDataToSlot(DefaultSlotName, 0); }

    UFUNCTION(BlueprintCallable)
    virtual void LoadData() { LoadDataFromSlot(DefaultSlotName, 0); }

    UFUNCTION(BlueprintCallable)
    virtual void SaveDataToSlot(FString SlotName, int32 SlotIndex);

    UFUNCTION(BlueprintCallable)
    virtual void LoadDataFromSlot(FString SlotName, int32 SlotIndex);

protected:
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    FString GetSaveName(const FString& SlotName, int32 SlotIndex) const;

    UFUNCTION(BlueprintNativeEvent)
    void OnSaveData();

    UFUNCTION(BlueprintNativeEvent)
    void OnLoadData();
};
