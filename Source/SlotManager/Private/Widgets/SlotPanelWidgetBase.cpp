// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SlotPanelWidgetBase.h"

#include "Components/UniformGridPanel.h"
#include "Interfaces/SlotManagerInterface.h"
#include "Interfaces/SlotWidgetInterface.h"

USlotPanelWidgetBase::USlotPanelWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SlotUpdatedHandler.BindDynamic(this, &ThisClass::OnSlotUpdated);
    SlotIndexChangedHandler.BindDynamic(this, &ThisClass::OnSlotIndexChanged);
}

void USlotPanelWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    FindSlotManager();
    BindSlotManagerEvents();
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

void USlotPanelWidgetBase::FindSlotManager()
{
    if (!SlotManagerClass) return;

    // Find SlotManager From PlayerController
    if (SlotManager.IsValid()) return;

    if (APlayerController* PlayerController = GetOwningPlayer())
    {
        if (PlayerController->IsA(SlotManagerClass))
        {
            SlotManager = PlayerController;
        }
        else if (UActorComponent* FoundComponent = PlayerController->GetComponentByClass(SlotManagerClass.Get()))
        {
            SlotManager = FoundComponent;
        }
    }

    // Find SlotManager From PlayerPawn
    if (SlotManager.IsValid()) return;

    if (APawn* PlayerPawn = GetOwningPlayerPawn())
    {
        if (PlayerPawn->IsA(SlotManagerClass))
        {
            SlotManager = PlayerPawn;
        }
        else if (UActorComponent* FoundComponent = PlayerPawn->GetComponentByClass(SlotManagerClass.Get()))
        {
            SlotManager = FoundComponent;
        }
    }
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
        int32 SlotNum  = PreviewSlotNum;
        if (SlotManager.IsValid() && SlotManager->Implements<USlotManagerInterface>())
        {
            SlotNum = ISlotManagerInterface::Execute_GetSlotNum(SlotManager.Get());
        }

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
    if (SlotManager.IsValid() && SlotManager->Implements<USlotManagerInterface>())
    {
        ISlotManagerInterface::Execute_BindSlotUpdatedHandler(SlotManager.Get(), SlotUpdatedHandler);
        ISlotManagerInterface::Execute_BindSlotIndexChangedHandler(SlotManager.Get(), SlotIndexChangedHandler);
    }
}

void USlotPanelWidgetBase::UnBindSlotManagerEvents()
{
    if (SlotManager.IsValid() && SlotManager->Implements<USlotManagerInterface>())
    {
        ISlotManagerInterface::Execute_UnBindSlotUpdatedHandler(SlotManager.Get(), SlotUpdatedHandler);
        ISlotManagerInterface::Execute_UnBindSlotIndexChangedHandler(SlotManager.Get(), SlotIndexChangedHandler);
    }
}

void USlotPanelWidgetBase::OnSlotIndexChanged_Implementation(int32 OldSlotIndex, int32 NewSlotIndex)
{

}

void USlotPanelWidgetBase::OnSlotUpdated_Implementation(int32 SlotIndex)
{
    if (UUserWidget* SlotWidget = SlotWidgetMap.FindRef(SlotIndex))
    {
        if (SlotWidget->Implements<USlotWidgetInterface>())
        {
            ISlotWidgetInterface::Execute_Refresh(SlotWidget);
        }
    }
}
