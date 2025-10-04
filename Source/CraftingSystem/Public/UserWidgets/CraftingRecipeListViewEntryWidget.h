// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "CraftingRecipeListViewEntryWidget.generated.h"

class UTextBlock;
class UImage;

/**
 *
 */
UCLASS(Abstract)
class CRAFTINGSYSTEM_API UCraftingRecipeListViewEntryWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UTextBlock> DisplayNameTextBock;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UImage> ThumbnailImage;

public:
    /* Components */

    FORCEINLINE UTextBlock* GetDisplayNameTextBock() const { return DisplayNameTextBock; }
    FORCEINLINE UImage* GetThumbnailImage() const { return ThumbnailImage; }

protected:
    /* IUserObjectListEntry */

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
