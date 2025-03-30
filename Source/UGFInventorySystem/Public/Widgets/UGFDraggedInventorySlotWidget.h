// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UGFDraggedInventorySlotWidget.generated.h"

class UImage;

/**
 *
 */
UCLASS()
class UGFINVENTORYSYSTEM_API UUGFDraggedInventorySlotWidget : public UUserWidget
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailImage(TSoftObjectPtr<UTexture2D> ThumbnailTexture);
};
