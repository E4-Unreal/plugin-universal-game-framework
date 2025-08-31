// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UGFDataManagerSubsystem.h"

#include "Components/CurrencyManagerComponent.h"
#include "Games/UGFSaveGame.h"

UUGFDataManagerSubsystem::UUGFDataManagerSubsystem()
{
    SaveGameClass = UUGFSaveGame::StaticClass();
}

void UUGFDataManagerSubsystem::OnSaveData_Implementation()
{
    UUGFSaveGame* CastedSaveGame = Cast<UUGFSaveGame>(SaveGame);
    if (CastedSaveGame == nullptr) return;

    APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();

    if (APawn* PlayerPawn = PlayerController->GetPawn())
    {
        if (UCurrencyManagerComponent* CurrencyManager = PlayerPawn->GetComponentByClass<UCurrencyManagerComponent>())
        {
            CastedSaveGame->CurrencyMap = CurrencyManager->GetCurrencyMap();
        }
    }
}

void UUGFDataManagerSubsystem::OnLoadData_Implementation()
{
    UUGFSaveGame* CastedSaveGame = Cast<UUGFSaveGame>(SaveGame);
    if (CastedSaveGame == nullptr) return;

    APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();

    if (APawn* PlayerPawn = PlayerController->GetPawn())
    {
        if (UCurrencyManagerComponent* CurrencyManager = PlayerPawn->GetComponentByClass<UCurrencyManagerComponent>())
        {
            CurrencyManager->SetCurrencyMap(CastedSaveGame->CurrencyMap);
        }
    }
}
