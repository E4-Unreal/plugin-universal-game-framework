// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonWidgetManagerSubsystem.generated.h"

class FButtonClickedDelegate;
class FPromptSubmittedDelegate;
class UCommonActivatableWidget;
class UCommonLayerWidgetBase;
class UCommonPlayerWidgetManagerComponent;

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGER_API UCommonWidgetManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintPure)
    virtual APlayerController* GetLocalPlayerController(AActor* PlayerActor) const;

    UFUNCTION(BlueprintPure)
    virtual UCommonPlayerWidgetManagerComponent* GetCommonPlayerWidgetManager(AActor* PlayerActor) const;

    UFUNCTION(BlueprintCallable)
    virtual void ShowAlertWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText);

    UFUNCTION(BlueprintCallable)
    virtual void ShowConfirmWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FButtonClickedDelegate& ConfirmButtonClickedDelegate);

    UFUNCTION(BlueprintCallable)
    virtual void ShowPromptWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric = false, int64 MinNum = 0, int64 MaxNum = 9999);

    UFUNCTION(BlueprintCallable)
    virtual UCommonActivatableWidget* ShowLayerWidget(AActor* PlayerActor, TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HideLayerWidget(AActor* PlayerActor, TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleLayerWidget(AActor* PlayerActor, TSubclassOf<UCommonLayerWidgetBase> WidgetClass);
};
