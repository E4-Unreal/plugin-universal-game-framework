// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "CurrencyTextWidget.generated.h"

class UCommonTextBlock;
class UCommonTextStyle;

/**
 *
 */
UCLASS()
class CURRENCYMANAGER_API UCurrencyTextWidget : public UCommonUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> CurrencyTextBlock;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayTag TargetCurrencyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int64 PreviewAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonTextStyle> TextStyle;

public:
    UCurrencyTextWidget();

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetCurrencyTextBlock() const { return CurrencyTextBlock; }

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCurrencyText(int64 NewAmount);

    void SetCurrencyTextStyle();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void BindEvent();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnUpdate(const FGameplayTag& CurrencyType, int64 Amount);
};
