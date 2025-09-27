// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/TargetWidgetInterface.h"
#include "SlotPanelWidgetBase.generated.h"

class UTextBlock;
class USlotManagerComponentBase;
class UUniformGridPanel;
class UDataObjectBase;

/**
 *
 */
UCLASS(Abstract)
class SLOTMANAGER_API USlotPanelWidgetBase : public UUserWidget, public ITargetWidgetInterface
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidgetOptional))
    TObjectPtr<UTextBlock> PanelNameTextBlock;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText PanelName;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<AActor> TargetActor;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<USlotManagerComponentBase> SlotManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, TObjectPtr<UUserWidget>> SlotWidgetMap;

public:
    USlotPanelWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* TargetWidgetInterface */

    virtual void SetTargetActor_Implementation(AActor* NewTargetActor) override;

    /* Components */

    FORCEINLINE UTextBlock* GetPanelNameTextBlock() const { return PanelNameTextBlock; }

protected:
    /* UserWidget */

    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;
    virtual void NativeDestruct() override;

    /* API */

    virtual void SetPanelName(const FText& NewPanelName);

    virtual void SetSlotManager(USlotManagerComponentBase* NewSlotManager);
    virtual void FindSlotManager();

    virtual void CreateSlotWidgets();
    virtual void UpdateSlotWidgets();
    virtual void InitializeSlotWidget(UUserWidget* SlotWidget, USlotManagerComponentBase* InSlotManager, int32 InSlotIndex);

    virtual void BindSlotManagerEvents();
    virtual void UnBindSlotManagerEvents();

    UFUNCTION(BlueprintNativeEvent)
    void OnSlotIndexChanged(int32 OldSlotIndex, int32 NewSlotIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnSlotUpdated(int32 Index);
};
