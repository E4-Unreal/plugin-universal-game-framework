// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPopupWidgetBase.h"
#include "CommonAlertWidgetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonAlertWidgetBase : public UCommonPopupWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonButtonBase> ConfirmButton;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonButtonBase* GetConfirmButton() const { return ConfirmButton; }

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnConfirmButtonClicked();
};
