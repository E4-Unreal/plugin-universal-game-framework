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

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    UFUNCTION(BlueprintPure)
    virtual APlayerController* GetOwningPlayerController() const;

    UFUNCTION(BlueprintCallable)
    virtual void ShowAlertWidget(const FText& TitleText, const FText& MessageText);

    UFUNCTION(BlueprintCallable)
    virtual void ShowConfirmWidget(const FText& TitleText, const FText& MessageText, const FButtonClickedDelegate& ConfirmButtonClickedDelegate);

    UFUNCTION(BlueprintCallable)
    virtual void ShowPromptWidget(const FText& TitleText, const FText& MessageText, const FPromptSubmittedDelegate& ConfirmButtonClickedDelegate, bool bShouldNumeric = false, int64 MinNum = 0, int64 MaxNum = 9999);

    UFUNCTION(BlueprintPure)
    UCommonLayoutWidgetBase* GetLayoutWidget() const { return LayoutWidget; }
};
