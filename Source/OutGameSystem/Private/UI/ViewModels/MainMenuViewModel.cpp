// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/MainMenuViewModel.h"

#include "UI/Interfaces/MainMenuModelInterface.h"

void UMainMenuViewModel::HandleOnStartButtonClicked()
{
    if (Model && Model->Implements<UMainMenuModelInterface>())
    {
        IMainMenuModelInterface::Execute_RequestStartGame(Model);
    }
}

void UMainMenuViewModel::HandleOnOptionsButtonClicked()
{
    if (Model && Model->Implements<UMainMenuModelInterface>())
    {
        IMainMenuModelInterface::Execute_OpenOptionsPanel(Model);
    }
}

void UMainMenuViewModel::HandleOnExitButtonClicked()
{
    if (Model && Model->Implements<UMainMenuModelInterface>())
    {
        IMainMenuModelInterface::Execute_RequestExitGame(Model);
    }
}

void UMainMenuViewModel::OnRefresh_Implementation()
{
    Super::OnRefresh_Implementation();

    if (Model->Implements<UMainMenuModelInterface>())
    {
        GameTitleText = IMainMenuModelInterface::Execute_GetGameTitleText(Model);
        VersionText = IMainMenuModelInterface::Execute_GetVersionText(Model);
    }
}
