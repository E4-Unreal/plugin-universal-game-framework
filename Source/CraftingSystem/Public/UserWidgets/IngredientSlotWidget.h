// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Item.h"
#include "IngredientSlotWidget.generated.h"

class UImage;
class UTextBlock;

/**
 *
 */
UCLASS(Abstract)
class CRAFTINGSYSTEM_API UIngredientSlotWidget : public UUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UTextBlock> OwnedQuantityTextBlock;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UTextBlock> NeededQuantityTextBlock;

public:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DesignerRebuild))
    FItem PreviewItem;
#endif

public:
    /* Widget */

    virtual void SynchronizeProperties() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewThumbnailTexture);

    UFUNCTION(BlueprintCallable)
    virtual void SetOwnedQuantity(int32 NewOwnedQuantity);

    UFUNCTION(BlueprintCallable)
    virtual void SetNeededQuantity(int32 NewNeededQuantity);

    UFUNCTION(BlueprintCallable)
    virtual void SetItem(const FItem& NewItem);

    /* Components */

    FORCEINLINE UImage* GetThumbnailImage() const { return ThumbnailImage; }
    FORCEINLINE UTextBlock* GetOwnedQuantityTextBlock() const { return OwnedQuantityTextBlock; }
    FORCEINLINE UTextBlock* GetNeededQuantityTextBlock() const { return NeededQuantityTextBlock; }
};
