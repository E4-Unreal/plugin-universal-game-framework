// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/Popup/CommonConfirmWidgetBase.h"
#include "Widgets/Popup/CommonPromptWidgetBase.h"
#include "CommonPlayerWidgetManagerComponent.generated.h"

class UCommonLayoutWidgetBase;
class UCommonAlertWidgetBase;

/**
 * PlayerController 전용 CommonWidgetManagerComponent
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class COMMONWIDGETMANAGER_API UCommonPlayerWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonLayoutWidgetBase> LayoutWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonAlertWidgetBase> AlertWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonConfirmWidgetBase> ConfirmWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonPromptWidgetBase> PromptWidgetClass;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UCommonLayoutWidgetBase> LayoutWidget;

public:
    UCommonPlayerWidgetManagerComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowAlertWidget(const FText& TitleText, const FText& MessageText);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowConfirmWidget(const FText& TitleText, const FText& MessageText, const FButtonClickedDelegate& ConfirmButtonClickedDelegate);

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* ShowPromptWidget(const FText& TitleText, const FText& MessageText, const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric = false, int64 MinNum = 0, int64 MaxNum = 9999);

    UFUNCTION(BlueprintCallable)
    virtual UCommonActivatableWidget* ShowLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual bool HideLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass);

    /* Getter */

    UFUNCTION(BlueprintPure)
    UCommonLayoutWidgetBase* GetLayoutWidget() const { return LayoutWidget; }

protected:
    APlayerController* GetOwningPlayerController() const;
};
