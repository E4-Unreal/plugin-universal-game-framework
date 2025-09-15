// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeSystemComponent.h"

#include "Logging.h"
#include "GameplayTags/AttributeGameplayTags.h"

UAttributeSystemComponent::UAttributeSystemComponent()
{
    bWantsInitializeComponent = true;

    AttributeConfigMap.Emplace(Attribute::Health, 100);
}

void UAttributeSystemComponent::InitializeComponent()
{
    Super::InitializeComponent();

    for (const auto& [AttributeType, MaxValue] : AttributeConfigMap)
    {
        if (AttributeType.IsValid() && MaxValue >= 0)
        {
            AttributeValueMap.Emplace(AttributeType, MaxValue);
        }
    }
}

void UAttributeSystemComponent::SetAttributeValue(FGameplayTag AttributeType, float NewValue)
{
    if (!HasAttribute(AttributeType)) return;

    const float MinValue = 0;
    const float MaxValue = GetMaxAttributeValue(AttributeType);
    const float OldValue = GetAttributeValue(AttributeType);
    NewValue = FMath::Clamp(NewValue, MinValue, MaxValue);

    if (FMath::IsNearlyEqual(OldValue, NewValue)) return;

    AttributeValueMap[AttributeType] = NewValue;

    HandleOnAttributeValueChanged(AttributeType, OldValue, NewValue);
    OnAttributeValueChanged.Broadcast(AttributeType, OldValue, NewValue);
}

void UAttributeSystemComponent::AddAttributeValue(FGameplayTag AttributeType, float ValueToAdd)
{
    if (!HasAttribute(AttributeType) || ValueToAdd < 0) return;

    const float CurrentValue = GetAttributeValue(AttributeType);
    float NewValue = CurrentValue + ValueToAdd;

    SetAttributeValue(AttributeType, NewValue);
}

void UAttributeSystemComponent::RemoveAttributeValue(FGameplayTag AttributeType, float ValueToRemove)
{
    if (!HasAttribute(AttributeType) || ValueToRemove < 0) return;

    const float CurrentValue = GetAttributeValue(AttributeType);
    float NewValue = CurrentValue - ValueToRemove;

    SetAttributeValue(AttributeType, NewValue);
}

void UAttributeSystemComponent::TakeDamage(float ActualDamage, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    RemoveAttributeValue(Attribute::Health, ActualDamage);
}

void UAttributeSystemComponent::HandleOnAttributeValueChanged_Implementation(FGameplayTag AttributeType, float OldValue,
                                                              float NewValue)
{
    LOG_ACTOR_COMPONENT(Log, TEXT("AttributeType: %s, OldValue: %f, NewValue: %f"), *AttributeType.GetTagName().ToString(), OldValue, NewValue)

    if (AttributeType == Attribute::Health)
    {
        if (FMath::IsNearlyZero(NewValue))
        {
            HandleOnDead();
            OnDead.Broadcast();
        }
        else if (FMath::IsNearlyZero(OldValue))
        {
            HandleOnRevived();
            OnRevived.Broadcast();
        }
        else if (OldValue > NewValue)
        {
            const float Damage = OldValue - NewValue;
            HandleOnDamaged(Damage);
            OnDamaged.Broadcast(Damage);
        }
        else
        {
            const float Heal = NewValue - OldValue;
            HandleOnHealed(Heal);
            OnHealed.Broadcast(Heal);
        }
    }
}

void UAttributeSystemComponent::HandleOnDamaged_Implementation(float Value)
{
    LOG_ACTOR_COMPONENT(Log, TEXT("Value: %f"), Value)
}

void UAttributeSystemComponent::HandleOnHealed_Implementation(float Value)
{
    LOG_ACTOR_COMPONENT(Log, TEXT("Value: %f"), Value)
}

void UAttributeSystemComponent::HandleOnDead_Implementation()
{
    LOG_ACTOR_COMPONENT(Log, TEXT(""))
}

void UAttributeSystemComponent::HandleOnRevived_Implementation()
{
    LOG_ACTOR_COMPONENT(Log, TEXT(""))
}
