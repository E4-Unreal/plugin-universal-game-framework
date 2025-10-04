// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "CraftingRecipeListViewEntryWidget.generated.h"

class UDataDefinitionBase;
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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UTextBlock> DisplayNameTextBlock;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

public:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DesignerRebuild))
    TObjectPtr<UDataDefinitionBase> PreviewRecipe;
#endif

public:
    /* Widget */

    virtual void SynchronizeProperties() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetDisplayName(const FText& NewDisplayName);

    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewThumbnailTexture);

    UFUNCTION(BlueprintCallable)
    virtual void SetRecipe(UDataDefinitionBase* NewRecipe);

    /* Components */

    FORCEINLINE UTextBlock* GetDisplayNameTextBlock() const { return DisplayNameTextBlock; }
    FORCEINLINE UImage* GetThumbnailImage() const { return ThumbnailImage; }

protected:
    /* IUserObjectListEntry */

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
