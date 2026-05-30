// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModels/AdvancedViewModel.h"
#include "MainMenuViewModel.generated.h"

/**
 *
 */
UCLASS()
class OUTGAMESYSTEM_API UMainMenuViewModel : public UAdvancedViewModel
{
    GENERATED_BODY()

private:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
    FText GameTitleText;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
    FText VersionText;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void HandleOnStartButtonClicked();

    UFUNCTION(BlueprintCallable)
    virtual void HandleOnOptionsButtonClicked();

    UFUNCTION(BlueprintCallable)
    virtual void HandleOnExitButtonClicked();

    /* Getter & Setter */

    // GameTitleText

    const FText& GetGameTitleText() const { return GameTitleText; }

    virtual void SetGameTitleText(const FText& NewGameTitleText)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(GameTitleText, NewGameTitleText))
        {
            UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GameTitleText);
        }
    }

    // VersionText

    const FText& GetVersionText() const { return VersionText; }

    virtual void SetVersionText(const FText& NewVersionText)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(VersionText, NewVersionText))
        {
            UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(VersionText);
        }
    }

protected:
    /* AdvancedViewModelBase */

    virtual void OnRefresh_Implementation() override;
};
