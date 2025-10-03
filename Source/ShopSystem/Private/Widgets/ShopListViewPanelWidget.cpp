// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewPanelWidget.h"

#include "Components/CurrencyManagerComponent.h"
#include "Components/ListView.h"
#include "Components/ShopComponent.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "Subsystems/WidgetManagerSubsystem.h"
#include "Widgets/BuyModalWidget.h"
#include "Widgets/ShopListViewEntryWidget.h"

UShopListViewPanelWidget::UShopListViewPanelWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    TargetComponentClass = UShopComponent::StaticClass();

    BuyPromptTitleText = NSLOCTEXT("ShopSystem", "BuyPromptTitleText", "Buy");
    BuyPromptMessageText = NSLOCTEXT("ShopSystem", "BuyPromptMessageText", "How many would you like to buy?");

    WidgetHiddenDelegate.BindDynamic(this, &ThisClass::OnWidgetHidden);
    PromptSubmittedDelegate.BindDynamic(this, &ThisClass::OnPromptSubmitted);
}

void UShopListViewPanelWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ShopListView)
    {
        auto& ItemDoubleClickedDelegate = ShopListView->OnItemDoubleClicked();
        ItemDoubleClickedDelegate.AddUObject(this, &ThisClass::OnItemDoubleClicked);
    }
}

void UShopListViewPanelWidget::BindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent)
{
    Super::BindTargetComponentEvents_Implementation(InTargetComponent);

    if (auto ShopComponent = Cast<UShopComponent>(TargetComponent))
    {
        ShopComponent->OnSlotUpdated.AddDynamic(this, &ThisClass::OnSlotUpdated);
    }

    InitializeShopListView();
}

void UShopListViewPanelWidget::UnbindTargetComponentEvents_Implementation(UActorComponent* InTargetComponent)
{
    Super::UnbindTargetComponentEvents_Implementation(InTargetComponent);

    if (auto ShopComponent = Cast<UShopComponent>(TargetComponent))
    {
        ShopComponent->OnSlotUpdated.RemoveDynamic(this, &ThisClass::OnSlotUpdated);
    }
}

void UShopListViewPanelWidget::InitializeShopListView()
{
    if (ShopListView && ShopListView->GetDefaultEntryClass())
    {
        ShopListView->ClearListItems();

        if (auto ShopComponent = Cast<UShopComponent>(TargetComponent))
        {
            const auto& ProductSlots = ShopComponent->GetSlots();

            for (int32 Index = 0; Index < ProductSlots.Num(); ++Index)
            {
                const auto& ProductSlot = ProductSlots[Index];
                auto Item = NewObject<UProductSlotContainer>();
                Item->Slot = ProductSlot;
                Item->Index = Index;
                ShopListView->AddItem(Item);
            }
        }
    }
}

void UShopListViewPanelWidget::OnItemDoubleClicked(UObject* Item)
{
    if (auto ProductSlotContainer = Cast<UProductSlotContainer>(Item))
    {
        // 구매 가능 수량 계산
        const auto& ProductSlot = ProductSlotContainer->Slot;
        auto Product = ProductSlot.Definition;
        const FGameplayTag CurrencyType = UProductDataFunctionLibrary::GetCurrencyType(Product);
        const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Product);
        const bool bInfiniteStock = ProductSlot.bInfiniteStock;
        const int32 Stock = ProductSlot.Stock;
        int32 AvailableQuantity = 1;

        // 재고 부족
        if (!bInfiniteStock && Stock <= 0) return;

        if (auto OwningPawn = GetOwningPlayerPawn())
        {
            if (auto CurrencyManager = OwningPawn->GetComponentByClass<UCurrencyManagerComponent>())
            {
                const int32 Currency = CurrencyManager->GetCurrencyByType(CurrencyType);

                // 1개도 구매가 불가능한 상황
                if (Currency < BuyPrice) return;

                AvailableQuantity = FMath::Clamp(Currency / BuyPrice, 1, Stock);
            }
        }

        // 구매 팝업 창 표시
        if (auto Subsystem = GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
        {
            Subsystem->ShowPromptWidget(GetOwningPlayer(), BuyPromptTitleText, BuyPromptMessageText, WidgetHiddenDelegate, PromptSubmittedDelegate, true, 1, AvailableQuantity);
        }
    }
}

void UShopListViewPanelWidget::OnSlotUpdated(int32 Index)
{
    if (ShopListView)
    {
        if (auto Item = Cast<UProductSlotContainer>(ShopListView->GetItemAt(Index)))
        {
            if (auto ShopComponent = Cast<UShopComponent>(TargetComponent))
            {
                Item->Slot = ShopComponent->GetSlot(Index);
            }

            if (auto EntryWidget = Cast<UShopListViewEntryWidget>(ShopListView->GetEntryWidgetFromItem(Item)))
            {
                EntryWidget->Refresh();
            }
        }
    }
}

void UShopListViewPanelWidget::OnWidgetHidden()
{
}

void UShopListViewPanelWidget::OnPromptSubmitted(const FText& SubmittedText)
{
    FString SubmittedString = SubmittedText.ToString();
    if (SubmittedString.IsNumeric())
    {
        int32 Quantity = FCString::Atoi(*SubmittedString);
        if (Quantity > 0)
        {
            if (auto ShopComponent = Cast<UShopComponent>(TargetComponent))
            {
                if (auto ProductSlotContainer = ShopListView->GetSelectedItem<UProductSlotContainer>())
                {
                    ShopComponent->BuyItem(GetOwningPlayerPawn(), ProductSlotContainer->Index, Quantity);
                }
            }
        }
    }
}
