// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuyModalWidget.h"

#include "ShopSystemFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/SpinBox.h"

void UBuyModalWidget::SetProduct(const TScriptInterface<IProductInterface>& NewProduct)
{
    Product = NewProduct;
}

void UBuyModalWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // 변수 초기화

    Customer = GetOwningPlayerPawn();

    // 이벤트 바인딩

    if (ConfirmButton)
    {
        ConfirmButton->OnClicked.AddDynamic(this, &ThisClass::OnConfirmButtonClicked);
    }

    if (CancelButton)
    {
        CancelButton->OnClicked.AddDynamic(this, &ThisClass::OnCancelButtonClicked);
    }
}

void UBuyModalWidget::OnConfirmButtonClicked_Implementation()
{
    UShopSystemFunctionLibrary::PurchaseProduct(Customer, Product, AmountSpinBox->GetValue());

    RemoveFromParent();
}

void UBuyModalWidget::OnCancelButtonClicked_Implementation()
{
    RemoveFromParent();
}
