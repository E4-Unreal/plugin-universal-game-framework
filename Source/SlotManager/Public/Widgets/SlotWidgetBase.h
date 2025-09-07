// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DraggableWidgetBase.h"
#include "Interfaces/SlotWidgetInterface.h"
#include "SlotWidgetBase.generated.h"

class USlotManagerComponentBase;
class UImage;

/**
 *
 */
UCLASS(Abstract)
class SLOTMANAGER_API USlotWidgetBase : public UDraggableWidgetBase, public ISlotWidgetInterface
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
    TWeakObjectPtr<USlotManagerComponentBase> SlotManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 SlotIndex;

public:
    /* SlotWidgetInterface */

    virtual USlotManagerComponentBase* GetSlotManager_Implementation() const override { return SlotManager.Get(); }
    virtual void SetSlotManager_Implementation(USlotManagerComponentBase* NewSlotManager) override;
    virtual int32 GetSlotIndex_Implementation() const override { return SlotIndex; }
    virtual void SetSlotIndex_Implementation(int32 NewSlotIndex) override;
    virtual void Refresh_Implementation() override;

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;

    /* DraggableWidgetBase */

    virtual bool CanDrag() const override;
    virtual void OnDraggedWidgetCreated(UUserWidget* DraggedWidget) override;
    virtual void OnWidgetDrop(UUserWidget* DropWidget) override;

    /* API */

    virtual void SetThumbnailTexture(UTexture2D* NewTexture);
    virtual void ApplyData(UDataAsset* InData);
    virtual void Clear();
};
