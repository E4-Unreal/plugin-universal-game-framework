// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/SlotManagerInterface.h"
#include "SlotPanelWidgetBase.generated.h"

class UUniformGridPanel;

/**
 *
 */
UCLASS(Abstract)
class WIDGETMANAGER_API USlotPanelWidgetBase : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> SlotPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "SlotManagerInterface"))
    TSubclassOf<UObject> SlotManagerClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "SlotWidgetInterface"))
    TSubclassOf<UUserWidget> SlotWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotColumn = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 PreviewSlotNum = 20;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UObject> SlotManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, TObjectPtr<UUserWidget>> SlotWidgetMap;

    FSlotUpdatedHandler SlotUpdatedHandler;
    FSlotIndexChangedHandler SlotIndexChangedHandler;

public:
    USlotPanelWidgetBase(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;
    virtual void NativeDestruct() override;

    virtual void FindSlotManager();

    virtual void ClearSlotWidgets();
    virtual void CreateSlotWidgets();

    virtual void BindSlotManagerEvents();
    virtual void UnBindSlotManagerEvents();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnSlotIndexChanged(int32 OldSlotIndex, int32 NewSlotIndex);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnSlotUpdated(int32 SlotIndex);
};
