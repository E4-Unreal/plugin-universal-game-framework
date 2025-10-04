// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/TargetWidgetBase.h"
#include "CraftingRecipeListViewPanelWidget.generated.h"

class UListView;
/**
 *
 */
UCLASS(Abstract)
class CRAFTINGSYSTEM_API UCraftingRecipeListViewPanelWidget : public UTargetWidgetBase
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UListView> ListView;

public:
    UCraftingRecipeListViewPanelWidget(const FObjectInitializer& ObjectInitializer);

    /* TargetWidgetBase */

    virtual void Refresh_Implementation() override;
    virtual void Clear_Implementation() override;

protected:
    FORCEINLINE UListView* GetListView() const { return ListView; }
};
