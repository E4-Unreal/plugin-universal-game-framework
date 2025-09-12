// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableCharacterBase.h"
#include "InteractableCharacter.generated.h"

class UWidgetComponent;

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableCharacter : public AInteractableCharacterBase
{
    GENERATED_BODY()

protected:
    static FName WidgetComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetComponent> WidgetComponent;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseCursorOverEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    FGameplayTag InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText InteractionMessage;

public:
    AInteractableCharacter(const FObjectInitializer& ObjectInitializer);

    /* Actor */

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginCursorOver() override;
    virtual void NotifyActorEndCursorOver() override;

    /* InteractableInterface */

    virtual FGameplayTag GetInteractionType_Implementation() const override { return InteractionType; }
    virtual FText GetInteractionMessage_Implementation() const override { return InteractionMessage; }
    virtual void SetFocus_Implementation(AActor* Interactor) override;
    virtual void ClearFocus_Implementation(AActor* Interactor) override;

public:
    FORCEINLINE UWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }
};
