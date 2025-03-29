// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/UGFInputConfig.h"
#include "InputTriggers.h"
#include "UGFInputConfig_UserWidget.generated.h"

class UUGFWidgetManagerComponent;
class UInputAction;

USTRUCT(Atomic, BlueprintType)
struct FUGFInputActionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputAction> InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETriggerEvent TriggerEvent = ETriggerEvent::Triggered;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UUserWidget> WidgetClass;

    bool IsValid() const;
};

/**
 *
 */
UCLASS(meta = (DisplayName = "UGFInputConfig_UserWidget"))
class UGFWIDGETSYSTEM_API UUGFInputConfig_UserWidget : public UUGFInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<FUGFInputActionData> InputActionDataList;

protected:
    static UUGFWidgetManagerComponent* GetWidgetManagerComponent(UEnhancedInputComponent* EnhancedInputComponent);

    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;
};
