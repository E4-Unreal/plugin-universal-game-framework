// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SaveGameSubsystem.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

USaveGameSubsystem::USaveGameSubsystem()
{
    DefaultSlotName = "Save";
}

bool USaveGameSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

void USaveGameSubsystem::SaveDataToSlot(FString SlotName, int32 SlotIndex)
{
    if (SaveGameClass == nullptr) return;

    if (SaveGame == nullptr) SaveGame = UGameplayStatics::CreateSaveGameObject(SaveGameClass);

    OnSaveData();
    OnSaveDataDelegate.Broadcast(SaveGame);

    UGameplayStatics::SaveGameToSlot(SaveGame, GetSaveName(SlotName, SlotIndex), 0);
}

void USaveGameSubsystem::LoadDataFromSlot(FString SlotName, int32 SlotIndex)
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
    {
        SaveGame = UGameplayStatics::LoadGameFromSlot(GetSaveName(SlotName, SlotIndex), 0);
        OnLoadData();
        OnLoadDataDelegate.Broadcast(SaveGame);
    }
}

FString USaveGameSubsystem::GetSaveName_Implementation(const FString& SlotName, int32 SlotIndex) const
{
    return SlotIndex == 0 ? SlotName : SlotName + "_" + FString::FromInt(SlotIndex);
}

void USaveGameSubsystem::OnSaveData_Implementation()
{
    // Save Data to SaveGame
}

void USaveGameSubsystem::OnLoadData_Implementation()
{
    // Load Data from SaveGame
}
