// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DamageableActorBase.h"

#include "Components/AttributeSystemComponent.h"
#include "GameplayTags/AttributeGameplayTags.h"
#include "Logging.h"

const FName ADamageableActorBase::AttributeSystemName(TEXT("AttributeSystem"));

ADamageableActorBase::ADamageableActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* SocketManager */

    AttributeSystem = CreateDefaultSubobject<UAttributeSystemComponent>(AttributeSystemName);
}

void ADamageableActorBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (GetAttributeSystem())
    {
        GetAttributeSystem()->OnAttributeValueChanged.AddDynamic(this, &ThisClass::HandleOnAttributeValueChanged);
    }
}

float ADamageableActorBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                       class AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    GetAttributeSystem()->RemoveAttributeValue(Attribute::Health, ActualDamage);

    return ActualDamage;
}

void ADamageableActorBase::OnDamaged(float Value)
{
    LOG_ACTOR(Log, TEXT("Value: %f"), Value)
}

void ADamageableActorBase::OnHealed(float Value)
{
    LOG_ACTOR(Log, TEXT("Value: %f"), Value)
}

void ADamageableActorBase::OnDead()
{
    LOG_ACTOR(Log, TEXT(""))
}

void ADamageableActorBase::OnRevived()
{
    LOG_ACTOR(Log, TEXT(""))
}

void ADamageableActorBase::HandleOnAttributeValueChanged(FGameplayTag AttributeType, float OldValue, float NewValue)
{
    if (AttributeType == Attribute::Health)
    {
        if (FMath::IsNearlyZero(NewValue))
        {
            OnDead();
        }
        else if (FMath::IsNearlyZero(OldValue))
        {
            OnRevived();
        }
        else if (OldValue > NewValue)
        {
            OnDamaged(OldValue - NewValue);
        }
        else
        {
            OnHealed(NewValue - OldValue);
        }
    }
}
