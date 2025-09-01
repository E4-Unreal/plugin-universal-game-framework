// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CommonWidgetManagerComponent.generated.h"


class UCommonLayoutWidgetBase;
class UCommonAlertWidgetBase;
class UCommonConfirmWidgetBase;
class FButtonClickedDelegate;
class UCommonPromptWidgetBase;
class FPromptSubmittedDelegate;

/**
 * PlayerController 전용 액터 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class COMMONWIDGETMANAGER_API UCommonWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonLayoutWidgetBase> LayoutWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "UI.Layer"))
    FGameplayTag PopupLayerTag;

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
    UCommonWidgetManagerComponent();

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
