// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Button.h"
#include "CommonPopupWidgetBase.generated.h"

class UCommonTextBlock;
class UCommonButtonBase;

DECLARE_DYNAMIC_DELEGATE(FButtonClickedDelegate);

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonPopupWidgetBase : public UCommonActivatableWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UCommonTextBlock> TitleTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> MessageTextBlock;

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTitleText(const FText& TitleText);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMessageText(const FText& MessageText);

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetTitleTextBlock() const { return TitleTextBlock; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetMessageTextBlock() const { return MessageTextBlock; }
};
