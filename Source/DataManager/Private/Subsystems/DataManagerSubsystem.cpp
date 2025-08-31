// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DataManagerSubsystem.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

UDataManagerSubsystem::UDataManagerSubsystem()
{
    DefaultSlotName = "Save";
}

bool UDataManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if(GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
    {
        return true;
    }

    return false;
}

void UDataManagerSubsystem::SaveDataToSlot(FString SlotName, int32 SlotIndex)
{
    if (SaveGameClass == nullptr) return;

    if (SaveGame == nullptr) SaveGame = UGameplayStatics::CreateSaveGameObject(SaveGameClass);

    OnSaveData();
    OnSaveDataDelegate.Broadcast(SaveGame);

    UGameplayStatics::SaveGameToSlot(SaveGame, GetSaveName(SlotName, SlotIndex), 0);
}

void UDataManagerSubsystem::LoadDataFromSlot(FString SlotName, int32 SlotIndex)
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
    {
        SaveGame = UGameplayStatics::LoadGameFromSlot(GetSaveName(SlotName, SlotIndex), 0);
        OnLoadData();
        OnLoadDataDelegate.Broadcast(SaveGame);
    }
}

FString UDataManagerSubsystem::GetSaveName_Implementation(const FString& SlotName, int32 SlotIndex) const
{
    return SlotIndex == 0 ? SlotName : SlotName + "_" + FString::FromInt(SlotIndex);
}

void UDataManagerSubsystem::OnSaveData_Implementation()
{
    // Save Data to SaveGame
}

void UDataManagerSubsystem::OnLoadData_Implementation()
{
    // Load Data from SaveGame
}
