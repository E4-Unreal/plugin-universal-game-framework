// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SlotPanelWidgetBase.h"

#include "Components/SlotManagerComponentBase.h"
#include "Components/UniformGridPanel.h"
#include "Interfaces/SlotWidgetInterface.h"

USlotPanelWidgetBase::USlotPanelWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void USlotPanelWidgetBase::SetTargetActor_Implementation(AActor* NewTargetActor)
{
    TargetActor = NewTargetActor ? NewTargetActor : GetOwningPlayerPawn();

    if (TargetActor.IsValid()) SetSlotManager(Cast<USlotManagerComponentBase>(TargetActor->GetComponentByClass(SlotManagerClass)));
}

void USlotPanelWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindSlotManager();
}

void USlotPanelWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    CreateSlotWidgets();
}

void USlotPanelWidgetBase::NativeDestruct()
{
    UnBindSlotManagerEvents();

    Super::NativeDestruct();
}

void USlotPanelWidgetBase::SetSlotManager(USlotManagerComponentBase* NewSlotManager)
{
    UnBindSlotManagerEvents();

    SlotManager = NewSlotManager;

    CreateSlotWidgets();
    BindSlotManagerEvents();
}

void USlotPanelWidgetBase::FindSlotManager()
{
    if (SlotManagerClass == nullptr) return;

    if (APawn* Pawn = GetOwningPlayerPawn())
    {
        SetSlotManager(Cast<USlotManagerComponentBase>(Pawn->GetComponentByClass(SlotManagerClass)));
    }
}

void USlotPanelWidgetBase::CreateSlotWidgets()
{
    // 유효성 검사
    if (SlotWidgetClass == nullptr) return;

    // 슬롯 수가 변경되지 않은 경우 무시
    const int32 OldSlotNum = SlotWidgetMap.Num();
    const int32 NewSlotNum  = SlotManager.IsValid() ? SlotManager->GetMaxSlotNum() : PreviewSlotNum;
    if (OldSlotNum == NewSlotNum) return;

    // 슬롯 위젯 생성
    if (OldSlotNum < NewSlotNum)
    {
        for (int32 Index = OldSlotNum; Index < NewSlotNum; ++Index)
        {
            UUserWidget* SlotWidget = CreateWidget<UUserWidget>(this, SlotWidgetClass);
            if (SlotWidget && SlotWidget->Implements<USlotWidgetInterface>())
            {
                ISlotWidgetInterface::Execute_SetSlotManager(SlotWidget, SlotManager.Get());
                ISlotWidgetInterface::Execute_SetSlotIndex(SlotWidget, Index);
            }

            int32 SlotColumn = Index % MaxSlotColumn;
            int32 SlotRow = Index / MaxSlotColumn;
            SlotPanel->AddChildToUniformGrid(SlotWidget, SlotRow, SlotColumn);

            SlotWidgetMap.Emplace(Index, SlotWidget);
        }
    }
    else
    {
        for (int32 Index = OldSlotNum - 1; Index >= NewSlotNum; --Index)
        {
            SlotPanel->RemoveChildAt(Index);
            SlotWidgetMap.Remove(Index);
        }
    }
}

void USlotPanelWidgetBase::BindSlotManagerEvents()
{
    if (SlotManager.IsValid())
    {
        SlotManager->OnSlotUpdated.AddDynamic(this, &USlotPanelWidgetBase::OnSlotUpdated);
    }
}

void USlotPanelWidgetBase::UnBindSlotManagerEvents()
{
    if (SlotManager.IsValid())
    {
        SlotManager->OnSlotUpdated.RemoveDynamic(this, &USlotPanelWidgetBase::OnSlotUpdated);
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
