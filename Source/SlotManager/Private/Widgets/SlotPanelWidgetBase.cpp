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

    Execute_SetTargetActor(this, nullptr);
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

    BindSlotManagerEvents();
}

void USlotPanelWidgetBase::ClearSlotWidgets()
{
    for (int32 Index = 0; Index < SlotWidgetMap.Num(); ++Index)
    {
        UUserWidget* SlotWidget = SlotWidgetMap[Index];
        SlotWidget->RemoveFromParent();
        SlotPanel->RemoveChildAt(Index);
    }
    SlotWidgetMap.Reset();
}

void USlotPanelWidgetBase::CreateSlotWidgets()
{
    ClearSlotWidgets();

    if (SlotWidgetClass)
    {
        // Get SlotNum
        int32 SlotNum  = SlotManager.IsValid() ? SlotManager->GetMaxSlotNum() : PreviewSlotNum;

        // Create SlotWidgets
        for (int32 Index = 0; Index < SlotNum; ++Index)
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
