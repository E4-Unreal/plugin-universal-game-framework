// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuyModalWidget.generated.h"

class UDataDefinitionBase;
class ICustomerInterface;
class IProductInterface;
class UButton;
class USpinBox;
/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UBuyModalWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USpinBox> AmountSpinBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ConfirmButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> CancelButton;

    UPROPERTY(VIsibleAnywhere, BlueprintReadOnly, Category = "State")
    TObjectPtr<AActor> Customer;

    UPROPERTY(VIsibleAnywhere, BlueprintReadOnly, Category = "State")
    TObjectPtr<UDataDefinitionBase> Product;

public:
    UFUNCTION(BlueprintCallable)
    void SetProduct(UDataDefinitionBase* NewProduct);

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnConfirmButtonClicked();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnCancelButtonClicked();
};
