// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ShopListViewEntryWidget.generated.h"

class UImage;
class UTextBlock;
class IProductInterface;

/**
 * ShopListViewPanelWidget의 EntryClass
 */
UCLASS()
class SHOPSYSTEM_API UShopListViewEntryWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DisplayNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> BuyPriceTextBlock;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TScriptInterface<IProductInterface> Product;

protected:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();
};
