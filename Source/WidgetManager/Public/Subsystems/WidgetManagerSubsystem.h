// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/PopupWidgetInterface.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WidgetManagerSubsystem.generated.h"

class UPlayerWidgetManagerComponent;
class FOnWidgetHidden;
class FOnButtonClicked;
class FOnPromptSubmitted;

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UWidgetManagerSubsystem : public ULocalPlayerSubsystem
{
    GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintPure)
    virtual APlayerController* GetLocalPlayerController(AActor* PlayerActor) const;

    UFUNCTION(BlueprintPure)
    virtual UPlayerWidgetManagerComponent* GetPlayerWidgetManager(AActor* PlayerActor) const;

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowAlertWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, TSubclassOf<UUserWidget> WidgetClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowConfirmWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, const FOnButtonClicked& ConfirmButtonClickedDelegate, TSubclassOf<UUserWidget> WidgetClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowPromptWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, const FOnPromptSubmitted& PromptSubmittedDelegate, bool bNumeric = false, float MinValue = 0.0f, float MaxValue = 10000.0f, TSubclassOf<UUserWidget> WidgetClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowWidget(AActor* PlayerActor, TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HideWidget(AActor* PlayerActor, TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(AActor* PlayerActor, TSubclassOf<UUserWidget> WidgetClass);
};
