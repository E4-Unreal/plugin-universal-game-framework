// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CraftingComponent.generated.h"


class UDataDefinitionBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class CRAFTINGSYSTEM_API UCraftingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 ToolType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config",  meta = (ClampMin = 0))
    int32 ToolGrade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSet<TObjectPtr<UDataDefinitionBase>> DefaultRecipes;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UDataDefinitionBase>> Recipes;

    FTimerHandle CraftingTimerHandle;

public:
    UCraftingComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    const TArray<UDataDefinitionBase*>& GetRecipes() const { return Recipes; }

    UFUNCTION(BlueprintPure)
    virtual bool HasRecipe(UDataDefinitionBase* InRecipe) const;

    UFUNCTION(BlueprintPure)
    virtual bool CanAddRecipe(UDataDefinitionBase* NewRecipe) const;

    UFUNCTION(BlueprintCallable)
    virtual void AddRecipe(UDataDefinitionBase* NewRecipe);

    UFUNCTION(BlueprintPure)
    virtual bool IsCrafting() const;

    UFUNCTION(BlueprintPure, meta = (DefaultToSelf = "Crafter"))
    virtual bool CanCraft(AActor* Crafter, UDataDefinitionBase* InRecipe) const;

    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Crafter"))
    virtual void StartCrafting(AActor* Crafter, UDataDefinitionBase* InRecipe);

    UFUNCTION(BlueprintCallable)
    virtual void PauseCrafting();

    UFUNCTION(BlueprintCallable)
    virtual void ResumeCrafting();

    UFUNCTION(BlueprintCallable)
    virtual void StopCrafting();

protected:
    /* Initialize */

    virtual void AddDefaultRecipes();

    /* Query */

    virtual bool HasIngredients(AActor* Crafter, UDataDefinitionBase* InRecipe) const;
    virtual void RemoveIngredients(AActor* Crafter, UDataDefinitionBase* InRecipe) const;
    virtual void AddResults(AActor* Crafter, UDataDefinitionBase* InRecipe) const;

    /* API */

    UFUNCTION()
    virtual void OnCraftingFinished(AActor* Crafter, UDataDefinitionBase* InRecipe);
};
