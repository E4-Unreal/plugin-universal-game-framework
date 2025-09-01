// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CommonWidgetManagerComponent.generated.h"


class FButtonClickedDelegate;
class UCommonLayoutWidgetBase;
class UCommonPopupWidgetBase;
class UCommonAlertWidgetBase;
class UCommonConfirmWidgetBase;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Popup", meta = (Categories = "UI.Layer"))
    FGameplayTag PopupLayerTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Popup")
    TSubclassOf<UCommonAlertWidgetBase> AlertWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Popup")
    TSubclassOf<UCommonConfirmWidgetBase> ConfirmWidgetClass;

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

    UFUNCTION(BlueprintPure)
    UCommonLayoutWidgetBase* GetLayoutWidget() const { return LayoutWidget; }
};
