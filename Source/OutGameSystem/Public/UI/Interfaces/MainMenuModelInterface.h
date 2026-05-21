// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainMenuModelInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UMainMenuModelInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class OUTGAMESYSTEM_API IMainMenuModelInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FText GetGameTitleText() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FText GetVersionText() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void RequestStartGame();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OpenOptionsPanel();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void RequestExitGame();
};
