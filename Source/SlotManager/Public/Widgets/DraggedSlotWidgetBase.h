// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/SlotWidgetInterface.h"
#include "DraggedSlotWidgetBase.generated.h"

class UImage;

/**
 *
 */
UCLASS(Abstract)
class SLOTMANAGER_API UDraggedSlotWidgetBase : public UUserWidget, public ISlotWidgetInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UTexture2D> DefaultThumbnailTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowedClasses = "SlotDataInterface"))
    TSoftObjectPtr<UDataAsset> PreviewData;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UActorComponent> SlotManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 SlotIndex;

public:
    UDraggedSlotWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* SlotWidgetInterface */

    virtual UActorComponent* GetSlotManager_Implementation() const override { return SlotManager.Get(); }
    virtual void SetSlotManager_Implementation(UActorComponent* NewSlotManager) override;
    virtual int32 GetSlotIndex_Implementation() const override { return SlotIndex; }
    virtual void SetSlotIndex_Implementation(int32 NewSlotIndex) override;
    virtual void Refresh_Implementation() override;

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;

    /* API */

    virtual void SetThumbnailTexture(UTexture2D* NewTexture);
    virtual void ApplyData(UDataAsset* InData);
    virtual void Clear();
};
