// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DamageableActorBase.h"

#include "Components/AttributeSystemComponent.h"

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
        GetAttributeSystem()->OnAttributeValueChanged.AddDynamic(this, &ThisClass::OnAttributeValueChanged);
        GetAttributeSystem()->OnDamaged.AddDynamic(this, &ThisClass::OnDamaged);
        GetAttributeSystem()->OnHealed.AddDynamic(this, &ThisClass::OnHealed);
        GetAttributeSystem()->OnDead.AddDynamic(this, &ThisClass::OnDead);
        GetAttributeSystem()->OnRevived.AddDynamic(this, &ThisClass::OnRevived);
    }
}

float ADamageableActorBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                       class AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    GetAttributeSystem()->TakeDamage(ActualDamage, DamageEvent, EventInstigator, DamageCauser);

    return ActualDamage;
}

void ADamageableActorBase::OnAttributeValueChanged_Implementation(FGameplayTag AttributeType, float OldValue, float NewValue)
{

}

void ADamageableActorBase::OnDamaged_Implementation(float Value)
{

}

void ADamageableActorBase::OnHealed_Implementation(float Value)
{

}

void ADamageableActorBase::OnDead_Implementation()
{

}

void ADamageableActorBase::OnRevived_Implementation()
{

}
