// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ItemDropActor.h"
#include "ResourceActor.generated.h"

class UAttributeSystemComponent;
struct FGameplayTag;

UCLASS()
class CRAFTINGSYSTEM_API AResourceActor : public AItemDropActor
{
    GENERATED_BODY()

protected:
    const static FName AttributeSystemName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAttributeSystemComponent> AttributeSystem;

public:
    AResourceActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual void Interact_Implementation(AActor* Interactor) override;

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
    FORCEINLINE UAttributeSystemComponent* GetAttributeSystem() const { return AttributeSystem; }

protected:
    /* API */

    UFUNCTION(BlueprintNativeEvent)
    void OnAttributeValueChanged(FGameplayTag AttributeType, float OldValue, float NewValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnDamaged(float Value);

    UFUNCTION(BlueprintNativeEvent)
    void OnHealed(float Value);

    UFUNCTION(BlueprintNativeEvent)
    void OnDead();

    UFUNCTION(BlueprintNativeEvent)
    void OnRevived();
};
