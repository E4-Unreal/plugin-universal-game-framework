// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewPanelWidget.h"

#include "Components/ListView.h"
#include "Components/ShopComponent.h"
#include "Widgets/BuyModalWidget.h"

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

    InitializeShopListView();
}

void UShopListViewPanelWidget::InitializeShopListView()
{
    if (ShopListView && ShopListView->GetDefaultEntryClass())
    {
        ShopListView->ClearListItems();

        if (auto ShopComponent = Cast<UShopComponent>(TargetComponent))
        {
            const auto& ProductSlots = ShopComponent->GetSlots();

            for (const auto& ProductSlot : ProductSlots)
            {
                auto Item = NewObject<UProductSlotContainer>();
                Item->Slot = ProductSlot;
                ShopListView->AddItem(Item);
            }
        }
    }
}

void UShopListViewPanelWidget::OnItemDoubleClicked(UObject* Item)
{
    // 구매 팝업 창 표시
}
