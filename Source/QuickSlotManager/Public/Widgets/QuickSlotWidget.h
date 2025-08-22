// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/QuickSlotWidgetBase.h"
#include "QuickSlotWidget.generated.h"

class IQuickSlotDataInterface;
class UQuickSlotManagerComponent;
class UImage;

/**
 *
 */
UCLASS(Abstract)
class QUICKSLOTMANAGER_API UQuickSlotWidget : public UQuickSlotWidgetBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TScriptInterface<IQuickSlotDataInterface> PreviewData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 SlotIndex;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetSlotIndex(int32 NewSlotIndex);

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

    UFUNCTION(BlueprintCallable)
    virtual void Clear();

    UFUNCTION(BlueprintCallable)
    virtual void ApplyData(const TScriptInterface<IQuickSlotDataInterface>& InData);

protected:
    virtual void NativePreConstruct() override;
};
