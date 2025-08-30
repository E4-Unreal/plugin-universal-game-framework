// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UGFGameInstance.generated.h"

class USaveGame;

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFGameInstance : public UGameInstance
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString RecentSaveSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString SaveSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Save")
    int32 MaxSaveSlotNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<USaveGame> SaveGameClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<USaveGame> SaveGame;

public:
    UUGFGameInstance();

    UFUNCTION(BlueprintCallable)
    virtual void SaveData() { SaveDataToSlot(RecentSaveSlotName, 0); }

    UFUNCTION(BlueprintCallable)
    virtual void LoadData() { LoadDataFromSlot(RecentSaveSlotName, 0); }

    UFUNCTION(BlueprintCallable)
    virtual void SaveDataToSlot(const FString& SlotName, const int32 SlotIndex = 0);

    UFUNCTION(BlueprintCallable)
    virtual void LoadDataFromSlot(const FString& SlotName, const int32 SlotIndex = 0);

protected:
    virtual void OnSaveData();
    virtual void OnLoadData();
};
