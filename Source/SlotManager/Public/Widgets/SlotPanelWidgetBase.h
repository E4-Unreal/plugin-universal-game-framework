// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotPanelWidgetBase.generated.h"

class USlotManagerComponentBase;
class UUniformGridPanel;
class UDataInstanceBase;

/**
 *
 */
UCLASS(Abstract)
class SLOTMANAGER_API USlotPanelWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<USlotManagerComponentBase> SlotManagerClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "SlotWidgetInterface"))
    TSubclassOf<UUserWidget> SlotWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotColumn = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 PreviewSlotNum = 20;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> SlotPanel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<USlotManagerComponentBase> SlotManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, TObjectPtr<UUserWidget>> SlotWidgetMap;

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
    void OnSlotUpdated(int32 Index, UDataInstanceBase* OldContent, UDataInstanceBase* NewContent);
};
