// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BuyModalWidget.h"

#include "Components/Button.h"
#include "Components/SpinBox.h"
#include "Interfaces/CustomerInterface.h"
#include "Interfaces/ProductInterface.h"

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
    if (!(Customer && Product)) return;

    // 구매 금액
    int32 Amount = AmountSpinBox->GetValue();
    int32 TotalBuyPrice = Amount * IProductInterface::Execute_GetBuyPrice(Product.GetObject());

    // 소지금
    FGameplayTag CurrencyType = IProductInterface::Execute_GetCurrencyType(Product.GetObject());
    int32 Budget = ICustomerInterface::Execute_GetCurrency(Customer.GetObject(), CurrencyType);

    // 소지금 부족
    if (Budget < TotalBuyPrice) return;

    // 소지금으로부터 구매 금액 차감 후 상품 지급
    ICustomerInterface::Execute_RemoveCurrency(Customer.GetObject(), CurrencyType, TotalBuyPrice);
    ICustomerInterface::Execute_AddProduct(Customer.GetObject(), Product);
}

void UBuyModalWidget::OnCancelButtonClicked_Implementation()
{
    RemoveFromParent();
}
