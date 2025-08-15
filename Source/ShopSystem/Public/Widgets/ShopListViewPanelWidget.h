// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopListViewPanelWidget.generated.h"

class IProductInterface;
class UListView;
class UBuyModalWidget;

/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UShopListViewPanelWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UListView> ShopListView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UBuyModalWidget> BuyModalWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TArray<TScriptInterface<IProductInterface>> DefaultProducts;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TArray<TScriptInterface<IProductInterface>> Products;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetProducts(const TArray<TScriptInterface<IProductInterface>>& NewProducts);

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void OnItemDoubleClicked(UObject* Item);
};
