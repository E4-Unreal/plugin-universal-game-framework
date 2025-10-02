// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ShopListViewEntryWidget.generated.h"

class UDataDefinitionBase;
class UBuyModalWidget;
class UImage;
class UTextBlock;
class IProductDataInterface;

/**
 * ShopListViewPanelWidget의 EntryClass
 */
UCLASS()
class SHOPSYSTEM_API UShopListViewEntryWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText StockTextFormat;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DisplayNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> BuyPriceTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> StockTextBlock;

public:
    UShopListViewEntryWidget(const FObjectInitializer& ObjectInitializer);

protected:
    /* IUserObjectListEntry */

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();
};
