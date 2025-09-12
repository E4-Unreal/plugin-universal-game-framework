// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionWidgetInterface.h"
#include "InteractionWidgetBase.generated.h"

class UTextBlock;

/**
 *
 */
UCLASS(Abstract)
class INTERACTIONSYSTEM_API UInteractionWidgetBase : public UUserWidget, public IInteractionWidgetInterface
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> InteractionTypeTextBlock;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> InteractionMessageTextBlock;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    TMap<FGameplayTag, FText> InteractionTypeTextMap;

public:
    UInteractionWidgetBase(const FObjectInitializer& ObjectInitializer);

    /* InteractionWidgetInterface */

    virtual void SetInteractionType_Implementation(FGameplayTag NewInteractionType) override;
    virtual void SetInteractionMessage_Implementation(const FText& NewInteractionMessage) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetInteractionTypeText(const FText& NewInteractionTypeText);

    UFUNCTION(BlueprintCallable)
    virtual void SetInteractionMessageText(const FText& NewInteractionMessageText);

public:
    UTextBlock* GetInteractionTypeTextBlock() const { return InteractionTypeTextBlock; }
    UTextBlock* GetInteractionMessageTextBlock() const { return InteractionMessageTextBlock; }
};
