// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Interfaces/MainMenuModelInterface.h"
#include "UObject/Object.h"
#include "MainMenuModelMock.generated.h"

/**
 * MainMenuViewModel 테스트 전용 Mock 클래스
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORKTESTS_API UMainMenuModelMock : public UObject, public IMainMenuModelInterface
{
    GENERATED_BODY()

private:
    bool bStartGameRequested;
    bool bOptionsPanelOpen;
    bool bExitGameRequested;

public:
    //~ Begin IModelInjectableInterface Interface
    virtual FText GetGameTitleText_Implementation() const override { return FText::FromString(TEXT("Test Game Title")); }
    virtual FText GetVersionText_Implementation() const override { return FText::FromString(TEXT("99.99.99")); }
    virtual void RequestStartGame_Implementation() override { bStartGameRequested = true; }
    virtual void OpenOptionsPanel_Implementation() override { bOptionsPanelOpen = true; }
    virtual void RequestExitGame_Implementation() override { bExitGameRequested = true; }
    //~ End IModelInjectableInterface Interface

    /* API */

    bool IsStartGameRequested() const { return bStartGameRequested; }
    bool IsOptionsPanelOpen() const { return bOptionsPanelOpen; }
    bool IsExitGameRequested() const { return bExitGameRequested; }
};
