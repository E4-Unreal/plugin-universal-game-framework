// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AttributeSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeValueChanged, FGameplayTag, AttributeType, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamaged, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealed, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevived);

UCLASS(meta = (BlueprintSpawnableComponent))
class ATTRIBUTESYSTEM_API UAttributeSystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnAttributeValueChanged OnAttributeValueChanged;

    UPROPERTY(BlueprintAssignable)
    FOnDamaged OnDamaged;

    UPROPERTY(BlueprintAssignable)
    FOnHealed OnHealed;

    UPROPERTY(BlueprintAssignable)
    FOnDead OnDead;

    UPROPERTY(BlueprintAssignable)
    FOnRevived OnRevived;

    // TMap<AttributeType, MaxValue>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Attribute", ClampMin = 0))
    TMap<FGameplayTag, float> AttributeConfigMap;

protected:
    // TMap<AttributeType, CurrentValue>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, float> AttributeValueMap;

public:
    UAttributeSystemComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool HasAttribute(FGameplayTag AttributeType) const { return AttributeValueMap.Contains(AttributeType); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetMaxAttributeValue(FGameplayTag AttributeType) const { return AttributeConfigMap.FindRef(AttributeType); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetAttributeValue(FGameplayTag AttributeType) const { return AttributeValueMap.FindRef(AttributeType); }

    UFUNCTION(BlueprintCallable)
    virtual void SetAttributeValue(FGameplayTag AttributeType, float NewValue);

    UFUNCTION(BlueprintCallable)
    virtual void AddAttributeValue(FGameplayTag AttributeType, float ValueToAdd);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveAttributeValue(FGameplayTag AttributeType, float ValueToRemove);

    UFUNCTION(BlueprintCallable)
    virtual void TakeDamage(float ActualDamage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
    /* API */

    virtual void HandleOnAttributeValueChanged(FGameplayTag AttributeType, float OldValue, float NewValue);
    virtual void HandleOnDamaged(float Value);
    virtual void HandleOnHealed(float Value);
    virtual void HandleOnDead();
    virtual void HandleOnRevived();
};
