// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/UGFGameInstance.h"

#include "Components/CurrencyManagerComponent.h"
#include "Games/UGFSaveGame.h"
#include "Kismet/GameplayStatics.h"

UUGFGameInstance::UUGFGameInstance()
{
    RecentSaveSlotName = "RecentSaveSlot";
    SaveSlotName = "SaveSlot";
    MaxSaveSlotNum = 4;
    SaveGameClass = UUGFSaveGame::StaticClass();
}

void UUGFGameInstance::SaveDataToSlot(const FString& SlotName, const int32 SlotIndex)
{
    if (SaveGame == nullptr) SaveGame = UGameplayStatics::CreateSaveGameObject(SaveGameClass);

    OnSaveData();

    UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, SlotIndex);
    if (SlotName != RecentSaveSlotName) UGameplayStatics::SaveGameToSlot(SaveGame, RecentSaveSlotName, 0);
}

void UUGFGameInstance::LoadDataFromSlot(const FString& SlotName, const int32 SlotIndex)
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
    {
        SaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
        OnLoadData();
    }
}

void UUGFGameInstance::OnSaveData()
{
    UUGFSaveGame* CastedSaveGame = Cast<UUGFSaveGame>(SaveGame);
    if (CastedSaveGame == nullptr) return;

    APlayerController* PlayerController = GetFirstLocalPlayerController();

    if (APawn* PlayerPawn = PlayerController->GetPawn())
    {
        if (UCurrencyManagerComponent* CurrencyManager = PlayerPawn->GetComponentByClass<UCurrencyManagerComponent>())
        {
            CastedSaveGame->CurrencyMap = CurrencyManager->GetCurrencyMap();
        }
    }
}

void UUGFGameInstance::OnLoadData()
{
    UUGFSaveGame* CastedSaveGame = Cast<UUGFSaveGame>(SaveGame);
    if (CastedSaveGame == nullptr) return;

    APlayerController* PlayerController = GetFirstLocalPlayerController();

    if (APawn* PlayerPawn = PlayerController->GetPawn())
    {
        if (UCurrencyManagerComponent* CurrencyManager = PlayerPawn->GetComponentByClass<UCurrencyManagerComponent>())
        {
            CurrencyManager->SetCurrencyMap(CastedSaveGame->CurrencyMap);

        }
    }
}
