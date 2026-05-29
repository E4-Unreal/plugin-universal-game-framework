// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interfaces/PopupWidgetInterface.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WidgetManagerSubsystem.generated.h"

class UWidgetStack;
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

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Getter, Category = "State", Transient)
    TObjectPtr<UUserWidget> LayoutWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, TObjectPtr<UWidgetStack>> LayerMap;

public:
    static UWidgetManagerSubsystem* Get(UObject* ContextObject);

    /* Subsystem */

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    /* LocalPlayerSubsystem */

    virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;

    /* ThisClass */

    UFUNCTION(BlueprintPure)
    FGameplayTag GetLayerTag(TSubclassOf<UUserWidget> WidgetClass) const;

    UFUNCTION(BlueprintPure, meta = (Categories = "UI.Layer"))
    UWidgetStack* GetWidgetStack(FGameplayTag LayerTag) const;

    UFUNCTION(BlueprintCallable)
    UUserWidget* ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    bool HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowAlertWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, TSubclassOf<UUserWidget> WidgetClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowConfirmWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, const FOnButtonClicked& ConfirmButtonClickedDelegate, TSubclassOf<UUserWidget> WidgetClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowPromptWidget(AActor* PlayerActor, const FText& TitleText, const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, const FOnPromptSubmitted& PromptSubmittedDelegate, bool bNumeric = false, float MinValue = 0.0f, float MaxValue = 10000.0f, TSubclassOf<UUserWidget> WidgetClass = nullptr);

    /* Getter & Setter */

    UUserWidget* GetLayoutWidget() const { return LayoutWidget; }

protected:
    virtual void CreateLayoutWidget(APlayerController* PlayerController);
    virtual void DestroyLayoutWidget();
};
