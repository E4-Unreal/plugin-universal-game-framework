// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SlotPanelWidgetBase.h"

#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Interfaces/SlotManagerInterface.h"
#include "Interfaces/SlotWidgetInterface.h"

USlotPanelWidgetBase::USlotPanelWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SlotUpdatedDelegate.BindDynamic(this, &ThisClass::OnSlotUpdated);
}

void USlotPanelWidgetBase::SetTargetActor_Implementation(AActor* NewTargetActor)
{
    TargetActor = NewTargetActor ? NewTargetActor : GetOwningPlayerPawn();

    if (TargetActor.IsValid() && SlotManagerClass)
    {
        SetSlotManager(TargetActor->GetComponentByClass(SlotManagerClass));
    }
}

void USlotPanelWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindSlotManager();
}

void USlotPanelWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetPanelName(PanelName);
    CreateSlotWidgets();
}

void USlotPanelWidgetBase::NativeDestruct()
{
    UnBindSlotManagerEvents();

    Super::NativeDestruct();
}

void USlotPanelWidgetBase::SetPanelName(const FText& NewPanelName)
{
    if (GetPanelNameTextBlock())
    {
        GetPanelNameTextBlock()->SetText(NewPanelName);
    }
}

void USlotPanelWidgetBase::SetSlotManager(UActorComponent* NewSlotManager)
{
    UnBindSlotManagerEvents();

    SlotManager = NewSlotManager;

    CreateSlotWidgets();
    UpdateSlotWidgets();
    BindSlotManagerEvents();
}

void USlotPanelWidgetBase::FindSlotManager()
{
    if (TargetActor.IsValid()) return;

    SetTargetActor(GetOwningPlayerPawn());
}

void USlotPanelWidgetBase::CreateSlotWidgets()
{
    // 유효성 검사
    if (SlotWidgetClass == nullptr) return;

    // 슬롯 수가 변경되지 않은 경우 무시
    const int32 OldSlotNum = SlotWidgetMap.Num();
    const int32 NewSlotNum  = SlotManager.IsValid() ? ISlotManagerInterface::Execute_GetMaxSlotNum(SlotManager.Get()) : PreviewSlotNum;
    if (OldSlotNum == NewSlotNum) return;

    // 슬롯 위젯 생성
    if (OldSlotNum < NewSlotNum)
    {
        for (int32 Index = OldSlotNum; Index < NewSlotNum; ++Index)
        {
            UUserWidget* SlotWidget = CreateWidget<UUserWidget>(this, SlotWidgetClass);
            InitializeSlotWidget(SlotWidget, SlotManager.Get(), Index);

            int32 SlotColumn = Index % MaxSlotColumn;
            int32 SlotRow = Index / MaxSlotColumn;
            GetSlotPanel()->AddChildToUniformGrid(SlotWidget, SlotRow, SlotColumn);

            SlotWidgetMap.Emplace(Index, SlotWidget);
        }
    }
    else
    {
        for (int32 Index = OldSlotNum - 1; Index >= NewSlotNum; --Index)
        {
            GetSlotPanel()->RemoveChildAt(Index);
            SlotWidgetMap.Remove(Index);
        }
    }
}

void USlotPanelWidgetBase::UpdateSlotWidgets()
{
    for (const auto& [Index, SlotWidget] : SlotWidgetMap)
    {
        InitializeSlotWidget(SlotWidget, SlotManager.Get(), Index);
    }
}

void USlotPanelWidgetBase::InitializeSlotWidget(UUserWidget* SlotWidget, UActorComponent* InSlotManager,
    int32 InSlotIndex)
{
    if (SlotWidget && SlotWidget->Implements<USlotWidgetInterface>())
    {
        ISlotWidgetInterface::Execute_SetSlotManager(SlotWidget, InSlotManager);
        ISlotWidgetInterface::Execute_SetSlotIndex(SlotWidget, InSlotIndex);
    }
}

void USlotPanelWidgetBase::BindSlotManagerEvents()
{
    if (SlotManager.IsValid())
    {
        ISlotManagerInterface::Execute_BindOnSlotUpdated(SlotManager.Get(), SlotUpdatedDelegate);
    }
}

void USlotPanelWidgetBase::UnBindSlotManagerEvents()
{
    if (SlotManager.IsValid())
    {
        ISlotManagerInterface::Execute_UnbindOnSlotUpdated(SlotManager.Get(), SlotUpdatedDelegate);
    }
}

void USlotPanelWidgetBase::OnSlotIndexChanged_Implementation(int32 OldSlotIndex, int32 NewSlotIndex)
{

}

void USlotPanelWidgetBase::OnSlotUpdated_Implementation(int32 Index)
{
    if (UUserWidget* SlotWidget = SlotWidgetMap.FindRef(Index))
    {
        if (SlotWidget->Implements<USlotWidgetInterface>())
        {
            ISlotWidgetInterface::Execute_Refresh(SlotWidget);
        }
    }
}
