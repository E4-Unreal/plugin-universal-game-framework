// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageableActorBase.generated.h"

class UAttributeSystemComponent;
struct FGameplayTag;

UCLASS(Abstract)
class ATTRIBUTESYSTEM_API ADamageableActorBase : public AActor
{
    GENERATED_BODY()

protected:
    const static FName AttributeSystemName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAttributeSystemComponent> AttributeSystem;

public:
    ADamageableActorBase(const FObjectInitializer& ObjectInitializer);

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
    FORCEINLINE UAttributeSystemComponent* GetAttributeSystem() const { return AttributeSystem; }

protected:
    /* API */

    UFUNCTION()
    virtual void OnAttributeValueChanged(FGameplayTag AttributeType, float OldValue, float NewValue);

    UFUNCTION()
    virtual void OnDamaged(float Value);

    UFUNCTION()
    virtual void OnHealed(float Value);

    UFUNCTION()
    virtual void OnDead();

    UFUNCTION()
    virtual void OnRevived();
};
