// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/UGFInventorySlotWidget.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/ShopComponent.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/InteractionSystemFunctionLibrary.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "Internationalization/StringTableRegistry.h"
#include "Subsystems/WidgetManagerSubsystem.h"

UUGFInventorySlotWidget::UUGFInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SellPromptTitleText = LOCTABLE("Shop", "SellPromptTitle");
    SellPromptMessageText = LOCTABLE("Shop", "SellPromptMessage");

    WidgetHiddenDelegate.BindDynamic(this, &ThisClass::OnWidgetHidden);
    PromptSubmittedDelegate.BindDynamic(this, &ThisClass::OnPromptSubmitted);
}

FReply UUGFInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
                                                               const FPointerEvent& InMouseEvent)
{
    if (SlotManager.IsValid() && SlotManager->Implements<USlotManagerInterface>())
    {
        if (!ISlotManagerInterface::Execute_IsSlotEmpty(SlotManager.Get(), SlotIndex))
        {
            if (IsTrading())
            {
                ShowSellPromptPopup();
            }
        }
    }

    return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

UShopComponent* UUGFInventorySlotWidget::GetShopComponent() const
{
    if (auto OwningPlayerPawn = GetOwningPlayerPawn())
    {
        if (auto InteractionSystem = OwningPlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
        {
            if (auto SelectedTarget = InteractionSystem->GetSelectedTarget())
            {
                return SelectedTarget->GetComponentByClass<UShopComponent>();
            }
        }
    }

    return nullptr;
}

bool UUGFInventorySlotWidget::IsPlayerInventory() const
{
    if (auto OwningPlayerPawn = GetOwningPlayerPawn())
    {
        return SlotManager.IsValid() && SlotManager->GetOwner() == OwningPlayerPawn;
    }

    return false;
}

bool UUGFInventorySlotWidget::IsTrading() const
{
    if (IsPlayerInventory())
    {
        if (auto OwningPlayerPawn = GetOwningPlayerPawn())
        {
            if (auto InteractionSystem = OwningPlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
            {
                if (auto SelectedTarget = InteractionSystem->GetSelectedTarget())
                {
                    if (auto ShopComponent = SelectedTarget->GetComponentByClass<UShopComponent>())
                    {
                        return UInteractionSystemFunctionLibrary::GetInteractor(SelectedTarget) == OwningPlayerPawn;
                    }
                }
            }
        }
    }

    return false;
}

void UUGFInventorySlotWidget::ShowSellPromptPopup() const
{
    if (auto Subsystem = GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        if (auto Inventory = Cast<UInventoryComponent>(SlotManager))
        {
            if (auto Content = Inventory->GetContent(SlotIndex))
            {
                int32 AvailableQuantity = UItemDataFunctionLibrary::GetQuantity(Content);
                if (AvailableQuantity > 0)
                {
                    Subsystem->ShowPromptWidget(GetOwningPlayer(), SellPromptTitleText, SellPromptMessageText, WidgetHiddenDelegate, PromptSubmittedDelegate, true, 1, AvailableQuantity);
                }
            }
        }
    }
}

void UUGFInventorySlotWidget::OnWidgetHidden()
{
}

void UUGFInventorySlotWidget::OnPromptSubmitted(const FText& SubmittedText)
{
    if (SubmittedText.IsNumeric())
    {
        int32 Quantity = FCString::Atoi(*SubmittedText.ToString());
        if (Quantity > 0)
        {
            if (auto Inventory = Cast<UInventoryComponent>(SlotManager))
            {
                if (auto Content = Inventory->GetContent(SlotIndex))
                {
                    if (auto ShopComponent = GetShopComponent())
                    {
                        ShopComponent->SellItem(GetOwningPlayerPawn(), Content->Definition, Quantity);
                    }
                }
            }
        }
    }
}
