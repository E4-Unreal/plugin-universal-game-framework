// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DraggableWidgetBase.h"
#include "Interfaces/SlotWidgetInterface.h"
#include "SlotWidgetBase.generated.h"

class UImage;

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API USlotWidgetBase : public UDraggableWidgetBase, public ISlotWidgetInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TScriptInterface<ISlotDataInterface> PreviewData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UObject> SlotManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 SlotIndex;

public:
    /* SlotWidgetInterface */

    virtual TScriptInterface<ISlotManagerInterface> GetSlotManager_Implementation() const override { return SlotManager.Get(); }
    virtual void SetSlotManager_Implementation(const TScriptInterface<ISlotManagerInterface>& NewSlotManager) override;
    virtual int32 GetSlotIndex_Implementation() const override { return SlotIndex; }
    virtual void SetSlotIndex_Implementation(int32 NewSlotIndex) override;
    virtual void ApplyData_Implementation(const TScriptInterface<ISlotDataInterface>& NewData) override;
    virtual void Refresh_Implementation() override;
    virtual void Clear_Implementation() override;

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;

    /* DraggableWidgetBase */

    virtual bool CanDrag() const override;
    virtual void OnDraggedWidgetCreated(UUserWidget* DraggedWidget) override;
};
