// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/TargetWidgetBase.h"
#include "CraftingRecipeViewPanelWidget.generated.h"

class UDataDefinitionBase;
class UTextBlock;
class UCommonNumericStepperWidget;
class UUniformGridView;
class UCommonButtonBase;
class UImage;

/**
 *
 */
UCLASS(Abstract)
class CRAFTINGSYSTEM_API UCraftingRecipeViewPanelWidget : public UTargetWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UTextBlock> DisplayNameTextBlock;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UTextBlock> QuantityTextBlock;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UCommonNumericStepperWidget> NumericStepper;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UUniformGridView> UniformGridView;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UCommonButtonBase> CraftButton;

public:
#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DesignerRebuild))
    TObjectPtr<UDataDefinitionBase> PreviewRecipe;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DesignerRebuild, ClampMin = 1))
    int32 PreviewQuantity = 1;
#endif

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UDataDefinitionBase> Recipe;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 Quantity;

public:
    UCraftingRecipeViewPanelWidget(const FObjectInitializer& ObjectInitializer);

    /* Widget */

    virtual void SynchronizeProperties() override;

    /* UserWidget */

    virtual void NativeOnInitialized() override;

    /* TargetWidgetBase */

    virtual void Refresh_Implementation() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetRecipe(UDataDefinitionBase* NewRecipe);

    UFUNCTION(BlueprintCallable)
    virtual void SetQuantity(int32 NewQuantity);

    UFUNCTION(BlueprintCallable)
    virtual void SetDisplayName(const FText& NewDisplayName);

    UFUNCTION(BlueprintCallable)
    virtual void SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewThumbnailTexture);

    UFUNCTION(BlueprintCallable)
    virtual void SetQuantityText(int32 NewQuantity);

    /* Events */

    UFUNCTION()
    virtual void OnCraftButtonClicked();

    UFUNCTION()
    virtual void OnNumericStepperValueChanged(int32 InValue);

    /* Components */

    FORCEINLINE UTextBlock* GetDisplayNameTextBlock() const { return DisplayNameTextBlock; }
    FORCEINLINE UTextBlock* GetQuantityTextBlock() const { return QuantityTextBlock; }
    FORCEINLINE UImage* GetThumbnailImage() const { return ThumbnailImage; }
    FORCEINLINE UCommonNumericStepperWidget* GetNumericStepper() const { return NumericStepper; }
    FORCEINLINE UUniformGridView* GetUniformGridView() const { return UniformGridView; }
    FORCEINLINE UCommonButtonBase* GetCraftButton() const { return CraftButton; }
};
