// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonWidgetManagerSubsystem.generated.h"

class FButtonClickedDelegate;
class FPromptSubmittedDelegate;

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGER_API UCommonWidgetManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintCallable)
    virtual void ShowAlertWidget(APlayerController* PlayerController, const FText& TitleText, const FText& MessageText);

    UFUNCTION(BlueprintCallable)
    virtual void ShowConfirmWidget(APlayerController* PlayerController, const FText& TitleText, const FText& MessageText, const FButtonClickedDelegate& ConfirmButtonClickedDelegate);

    UFUNCTION(BlueprintCallable)
    virtual void ShowPromptWidget(APlayerController* PlayerController, const FText& TitleText, const FText& MessageText, const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric = false, int64 MinNum = 0, int64 MaxNum = 9999);
};
